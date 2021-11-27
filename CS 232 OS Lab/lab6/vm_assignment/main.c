/*
Main program for the virtual memory project.
Make all of your modifications to this file.
You may add or rearrange any code or data as you need.
The header files page_table.h and disk.h explain
how to use the page table and disk interfaces.
*/


#include "page_table.h"
#include "disk.h"
#include "program.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int npages, nframes;

int faultCount,writeCount,readCount;

char *physmem;

struct disk *disk;

//Create pointers to page frame for free list
struct page_pointer{
  int page;
  struct page_pointer *next;
};

struct page_pointer *free_list;
struct page_pointer *fifo_head;
struct page_pointer *fifo_tail;

struct frame_entry{
  int bits;
  int page;
};

struct page_pointer *fifo_2_head;
struct page_pointer *fifo_2_tail;

struct frame_entry *fifo_2_frame_entries;
int fifo_1_length;

int algorithm;


int freeList()
{
  int frame;
  if(free_list != NULL) {
    //printf("freelist page = %d",free_list->page);
    frame = free_list->page;
    struct page_pointer *temp = free_list;
    free_list = free_list->next;
    free(temp);
  }
  else {
    frame = -1;
  }
  return frame;
}

//Only called by fifo2 methods to move from fifo1 to fifo2
void fifo_2_add(int frame){
  //Add new page to fifo2

  fifo_2_tail->next = malloc(sizeof(struct page_pointer));
  fifo_2_tail = fifo_2_tail->next;
  fifo_2_tail->page = frame;
  fifo_2_tail->next = NULL;

}



int fifo_evict_page(){

  int frame;

  //Get frame to be evicted and remove from fifo
  frame = (fifo_head->next)->page;
  struct page_pointer *temp = fifo_head;
  fifo_head = fifo_head->next;
  free(temp);

  return frame;
}

void fifo_add_page(int frame){
  //Add new page to fifo
  fifo_tail->next = malloc(sizeof(struct page_pointer));
  fifo_tail = fifo_tail->next;
  fifo_tail->page = frame;
  fifo_tail->next = NULL;
}

//Pages added to 2nd chance fifo through this
void fifo_2_add_page(struct page_table *pt, int frame){
  if(fifo_1_length == nframes - nframes/4){
    int fifo_2_frame = fifo_evict_page();
    int evictPage,framePointer,bitPointer;

    evictPage = 0;
    while(evictPage < npages)//npages is the total number of pages
      {
	page_table_get_entry(pt,evictPage,&framePointer,&bitPointer);
	if(framePointer == fifo_2_frame && bitPointer != 0)
	  break;
	evictPage++;
      }

    fifo_2_frame_entries[fifo_2_frame].bits = bitPointer;
    fifo_2_frame_entries[fifo_2_frame].page = evictPage;

    page_table_set_entry(pt,evictPage,fifo_2_frame,0);//clear protection bits of virtual page pointing to frame
    fifo_2_add(fifo_2_frame);
  }
  else
    fifo_1_length++;

  fifo_add_page(frame);
}

//Pages removed from 2nd chance fifo through this
int fifo_2_evict_page(struct page_table *pt){

  int frame;


  //Get frame to be evicted and remove from fifo
  frame = (fifo_2_head->next)->page;

  struct page_pointer *temp = fifo_2_head;
  fifo_2_head = fifo_2_head->next;
  free(temp);

  //Reset protection bits on the page
  page_table_set_entry(pt,fifo_2_frame_entries[frame].page,frame,fifo_2_frame_entries[frame].bits);
  //Clear protection bits from frame table
  fifo_2_frame_entries[frame].bits = 0;

  return frame;
}



//Checks for page to be on 2nd chance fifo
int fifo_2_page_referenced(struct page_table *pt, int page){
  int i;
  for(i = 0; i < nframes; i++){
    //printf("frame table %d: page = %d: bits = %d\n",i,fifo_2_frame_entries[i].page,fifo_2_frame_entries[i].bits);
    if(fifo_2_frame_entries[i].page == page &&
       fifo_2_frame_entries[i].bits != 0){
      break;
    }
  }

  if(i == nframes){
    return 0;
  }

  struct page_pointer *temp = fifo_2_head;
  while(temp->next != NULL){
    if((temp->next)->page == i){
      struct page_pointer *delTemp = temp->next;
      if(temp->next == fifo_2_tail)
	fifo_2_tail = temp;
      temp->next = (temp->next)->next;
      free(delTemp);
      break;
    }
    temp = temp-> next;
  }

  //Reset protection bits on the page
  page_table_set_entry(pt,page,i,fifo_2_frame_entries[i].bits);
  //Clear protection bits from frame table
  fifo_2_frame_entries[i].bits = 0;

  fifo_2_add_page(pt,i);


  return 1;
}

void page_fault_handler( struct page_table *pt, int page)
{
  faultCount++;
  printf("page fault on page #%d\n",page);

  int rw, frame, i=0,evictPage=0; //rw tells us if the page fault is due to a read or a write
  //frame is obtained either via free lists or from the page replacement algorithm
  //frame = -1 if there is no page left to allocate(obtained from the free lists)
  //0 <= frame < nframes when the page replacement algorithm is called
  int framePointer, bitPointer; //frame of returned page from Virtual Memory & returned bits

  if(algorithm == 2){
    if(fifo_2_page_referenced(pt,page) == 1){
      printf("returning\n");
      return;
    }
  }


  //////////////////////////////////////////////////////
  //setting rw//
  page_table_get_entry(pt,page,&framePointer,&bitPointer);
  //if(bitPointer[0]==0 && bitPointer[1]==0)
  if(bitPointer == 0)
    {
      rw = 0; //page fault was due to a READ operation
    }
  else if(bitPointer == PROT_READ)
    {
      rw = 1; //page fault was due to a WRITE operation
      page_table_set_entry(pt,page,framePointer,PROT_READ|PROT_WRITE);
    }


  if(rw == 0) //if page is not in memory or invalid
    {
      int frame = freeList();
      if(frame >= 0) //physical memory has empty locations
	{
	  //Add frames for fifo algorithms
	  if(algorithm == 1)
	    fifo_add_page(frame);
	  else if(algorithm == 2)
	    fifo_2_add_page(pt,frame);

	  page_table_set_entry(pt,page,frame,PROT_READ);

	}

      else if(frame == -1) //frame=-1 so physical memory is filled
	{
	  switch(algorithm){
	  case 0:
	    frame = (lrand48() % nframes); //this is where the page is to be written, frame number
	    break;
	  case 1:
	    frame = fifo_evict_page();
	    fifo_add_page(frame);
	    break;
	  case 2:
	    frame = fifo_2_evict_page(pt);
	    fifo_2_add_page(pt,frame);
	    break;
	  }

	  evictPage = 0;
	      while(evictPage < npages)//npages is the total number of pages
	      {
		  page_table_get_entry(pt,evictPage,&framePointer,&bitPointer);

		  if(evictPage != page && bitPointer == 1 && framePointer == frame) // page mapping to the frame which is to be replaced has only Read bit
		  {
		  //frame found; R bit set
		  page_table_set_entry(pt,evictPage,frame,0);//unmap current mapping and free the frame
		  page_table_set_entry(pt,page,frame,PROT_READ);// map the current frame to the page
		  disk_read(disk,page,&physmem[frame*PAGE_SIZE]);//overwrite contents
		  break;
		  }
		  else if(evictPage != page && framePointer == frame && bitPointer == 3) // page mapping to the frame which is to be replaced has Read and Write bit

		  {
		    //frame found; RW bit set
		    disk_write(disk,evictPage,&physmem[frame*PAGE_SIZE]);//write page(to be evicted) to disk
		    disk_read(disk,page,&physmem[frame*PAGE_SIZE]);//load required page to disk
		    page_table_set_entry(pt,page,frame,PROT_READ);
		    page_table_set_entry(pt,evictPage,frame,0);//set the evicted page as invalid
		    writeCount++;

		    break;
		  }
	          evictPage++;
	      }
	      readCount++;
	      //printf("new page %d : evicted page %d : frame #%d = %d\n",page,evictPage,frame,framePointer);
	}

    }

  //page_table_print(pt);
}





int main( int argc, char *argv[] )
{
	if(argc!=5) {
		printf("use: virtmem <npages> <nframes> <rand|fifo|custom> <sort|scan|focus>\n");
		return 1;
	}

	faultCount = 0;
	readCount = 0;
	writeCount = 0;

	npages = atoi(argv[1]);
	nframes = atoi(argv[2]);
	const char *program = argv[4];
	const char *page_algorithm = argv[3];

	//Initialize free list
	int i;
	free_list = NULL;
	struct page_pointer *temp;
	for(i = nframes - 1; i > -1; i--){
	  temp = malloc(sizeof(struct page_pointer));
	  temp->page = i;
	  temp->next = free_list;
	  free_list = temp;
	}


	//Initialize fifo pointers
	fifo_head = malloc(sizeof(struct page_pointer));
	fifo_head->next = NULL;
	fifo_tail = fifo_head;

	//Init fifo1_length and frame table
	fifo_1_length = 0;
	fifo_2_frame_entries = malloc(sizeof(struct frame_entry)*nframes);

	//init fifo_2 pointers
	fifo_2_head = malloc(sizeof(struct page_pointer));
	fifo_2_head->next = NULL;
	fifo_2_tail = fifo_2_head;

	unsigned short seedv[3]={1,1,1};
	seed48(seedv);


	disk = disk_open("myvirtualdisk",npages);
	if(!disk) {
		fprintf(stderr,"couldn't create virtual disk: %s\n",strerror(errno));
		return 1;
	}


	struct page_table *pt = page_table_create( npages, nframes, page_fault_handler );
	if(!pt) {
		fprintf(stderr,"couldn't create page table: %s\n",strerror(errno));
		return 1;
	}

	char *virtmem = page_table_get_virtmem(pt);

        physmem = page_table_get_physmem(pt);


	//Decide on page replacement algorithm to use
	if(!strcmp(page_algorithm,"rand")){
	  algorithm = 0;
	}
	else if(!strcmp(page_algorithm,"fifo")){
	  algorithm = 1;
	}
	else if(!strcmp(page_algorithm,"custom")){
	  algorithm = 2;
	}
	else{
	  fprintf(stderr,"unknown replacement algorithm: %s\n",page_algorithm);
	  return 1;
	}



	if(!strcmp(program,"sort")) {
		sort_program(virtmem,npages*PAGE_SIZE);

	} else if(!strcmp(program,"scan")) {
		scan_program(virtmem,npages*PAGE_SIZE);

	} else if(!strcmp(program,"focus")) {
		focus_program(virtmem,npages*PAGE_SIZE);

	} else {
		fprintf(stderr,"unknown program: %s\n",argv[3]);

	}

	page_table_delete(pt);
	disk_close(disk);

	printf("# Page Faults = %d\n# Reads = %d\n # Writes = %d\n",
	       faultCount,readCount,writeCount);

	return 0;
}
