// fs.cpp: File System

#include "sfs/fs.h"

#include <algorithm>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include<math.h>

int block_bitmap[100];
// Debug file system -----------------------------------------------------------
void FileSystem::debug(Disk *disk) {
    Block superblock;

    // Read Superblock
    disk->read(0, superblock.Data);

    printf("My output\n");
    printf("SuperBlock:\n");
    if (superblock.Super.MagicNumber == MAGIC_NUMBER) {
        printf("    magic number is valid\n");
    }
    printf("    %u blocks\n", superblock.Super.Blocks);
    printf("    %u inode blocks\n", superblock.Super.InodeBlocks);
    printf("    %u inodes\n", superblock.Super.Inodes);

    Block inode_block;
    for (uint block_index = 1; block_index <= superblock.Super.InodeBlocks;
         block_index++) {

        disk->read(block_index,
                   inode_block.Data); // read the inodes into `inode_block`

        for (uint inode_index = 0; inode_index < INODES_PER_BLOCK;
             inode_index++) {
            Inode inode = inode_block.Inodes[inode_index];

            if (inode.Valid) {
                printf("Inode %u:\n", inode_index);
                printf("    size: %u bytes\n", inode.Size);
                printf("    direct blocks:");

                for (uint direct_block_indexer : inode.Direct) {
                    if (direct_block_indexer == 0) {
                        break;
                    }

                    printf(" %u", direct_block_indexer);
                }
                printf("\n");

                if (inode.Indirect != 0) {
                    printf("    indirect block: %u\n", inode.Indirect);

                    Block indirect_block;
                    disk->read(inode.Indirect, indirect_block.Data);

                    printf("    indirect data blocks:");
                    for (uint indirect_block_indexer :
                         indirect_block.Pointers) {
                        if (indirect_block_indexer == 0) {
                            break;
                        }

                        printf(" %u", indirect_block_indexer);
                    }
                    printf("\n");
                }
            }
        }
    }
}

bool FileSystem::format(Disk *disk) {
    // Write superblock
    Block superblock;
    superblock.Super.MagicNumber = MAGIC_NUMBER;
    superblock.Super.Blocks = disk->size();
    superblock.Super.InodeBlocks = std::max(1, (int)disk->size() / 10);
    superblock.Super.Inodes = (superblock.Super.InodeBlocks) * INODES_PER_BLOCK;

    disk->write(0, superblock.Data);

    char Data[Disk::BLOCK_SIZE] = {'\0'};
    for (uint block_index = 1; block_index < superblock.Super.Blocks;
         block_index++) {
        disk->write(block_index, Data);
    }

    return true;
}


bool FileSystem::mount(Disk *disk) {
    // Read superblock
    if(disk->mounted()){
            return false;
    }
    Block block;
    disk->read(0,block.Data);
    if(block.Super.Inodes !=block.Super.InodeBlocks* INODES_PER_BLOCK){
            return false;
    }

    if(block.Super.MagicNumber !=MAGIC_NUMBER){
            return false;
    }

    if(block.Super.Blocks<0){
            return false;
    }

    if(block.Super.InodeBlocks != ceil(0.1 * block.Super.Blocks)){
            return false;
    }


    // Set device and mount
    disk->mount();
    // Copy metadata
     blocks=block.Super.Blocks;
    inode_blocks=block.Super.InodeBlocks;
     inodes=block.Super.Inodes;
     this->disk=disk;

   block_bitmap = std::vector<int> (blocks,1);

    //set all blocks to free initially
    for (uint32_t i = 0; i < blocks; i++) {
        block_bitmap[i] = 1;
   }

  // Allocate free block bitmap
    block_bitmap[0]=0;

    for(uint i=0;i<inode_blocks;i++){

            block_bitmap[i+1]=0;
    }

    for(uint inode_index=0;inode_index<inode_blocks;inode_index++){
            Block temp;
            disk->read(inode_index+1,temp.Data);

            for(uint i_index=0; i_index<INODES_PER_BLOCK;i_index++){
                    if(!temp.Inodes[i_index].Valid)
                            continue;
                    uint n_blocks=(uint) ceil(temp.Inodes[i_index].Size/(double)disk->BLOCK_SIZE);
                    for(uint pointer=0; pointer<POINTERS_PER_BLOCK && pointer<n_blocks;pointer++){
                            block_bitmap[temp.Inodes[i_index].Direct[pointer]]=0;

                    }

                    if(n_blocks>POINTERS_PER_INODE){
                            Block indirect;
                            disk->read(temp.Inodes[i_index].Indirect, indirect.Data);
                            block_bitmap[temp.Inodes[i_index].Indirect]=0;
                            for(uint pointer=0;pointer<n_blocks-POINTERS_PER_INODE;pointer++){
                                    block_bitmap[indirect.Pointers[pointer]]=0;
                            }
                    }
            }
    }
    return true;
}

ssize_t FileSystem::create() {
    // Locate free inode in inode table

       int ind = -1;
    for (uint32_t inode_block = 0; inode_block < inode_blocks; inode_block++) {
        Block b;
        disk->read(1+inode_block,b.Data);
        // reads each inode
        for (uint32_t inode = 0; inode < INODES_PER_BLOCK; inode++) {
            // if it's not valid, it's free to be written
            if (!b.Inodes[inode].Valid) {
                ind = inode + INODES_PER_BLOCK*inode_block;
                break;
            }
        }
        if (ind != -1) {
            break;
        }
    }


    // Record inode if found
     if (ind == -1) {
        return -1;
    }
    Inode i;
    i.Valid = true;
    i.Size = 0;
    for (unsigned int j = 0; j < POINTERS_PER_INODE; j++) {
        i.Direct[j] = 0;
    }
    i.Indirect = 0;
    save_inode(ind, &i);

    return ind;

}

bool FileSystem::remove(size_t inumber) {
    Inode node;

    // Load inode information
    if (!load_inode(inumber, &node)) {
        return false;
    }
    if (node.Valid == 0) {
        return false;
    }

    // Free direct blocks
    for (unsigned int i = 0; i < POINTERS_PER_INODE; i++) {
        if (node.Direct[i] != 0) {
            block_bitmap[node.Direct[i]] = 1;
            node.Direct[i] = 0;
        }
    }

    // Free indirect blocks
    if (node.Indirect != 0) {
        block_bitmap[node.Indirect] = 1;
        Block b;
        disk->read(node.Indirect,b.Data);
        // Free blocks pointed to indirectly
        for (unsigned int i = 0; i < POINTERS_PER_BLOCK; i++) {
            if (b.Pointers[i] != 0) {
                block_bitmap[b.Pointers[i]] = 1;
            }
        }
    }
    // Clear inode in inode table
    node.Indirect = 0;
    node.Valid = 0;
    node.Size = 0;
    if (!save_inode(inumber, &node)) {
        return false;
    };


    return true;
}

ssize_t FileSystem::stat(size_t inumber) {
    // Load inode information
     Inode i;
    if (!load_inode(inumber,&i) || !i.Valid) {
        return -1;
    }

    return i.Size;
    return 0;
}

ssize_t FileSystem::read(size_t inumber, char *data, size_t length, size_t offset) {
 // Load inode information
 Inode inode;
 if (!load_inode(inumber, &inode) || offset > inode.Size) {
 return -1;
 }

 // Adjust length
 length = std::min(length, inode.Size - offset);

 uint32_t start_block = offset / disk->BLOCK_SIZE;

 // Read block and copy to data; use memcpy

 // Get indirect block number if it will need it
 Block indirect;
 if ((offset + length) / disk->BLOCK_SIZE > POINTERS_PER_INODE) {
 // make sure direct block is allocated
 if (inode.Indirect == 0) {
 return -1;
 }
 disk->read(inode.Indirect,indirect.Data);
 }

 size_t read = 0;
 for (uint32_t block_num = start_block; read < length; block_num++) {
 
 // figure out which block we're reading
 size_t block_to_read;
 if (block_num < POINTERS_PER_INODE) {
 block_to_read = inode.Direct[block_num];
 } else {
 block_to_read = indirect.Pointers[block_num-POINTERS_PER_INODE];
 }

 //make sure block is allocated
 if (block_to_read == 0) {
 return -1;
 }

 //get the block -- from either direct or indirect
 Block b;
 disk->read(block_to_read,b.Data);
 size_t read_offset;
 size_t read_length;

 // if it's the first block read, have to start from an offset
 // and read either until the end of the block, or the whole request
 if (read == 0) {
 read_offset = offset % disk->BLOCK_SIZE;
 read_length = std::min(disk->BLOCK_SIZE - read_offset, length);
 } else {
 // otherwise, start from the beginning, and read
 // either the whole block or the rest of the request
 read_offset = 0;
 read_length = std::min(disk->BLOCK_SIZE-0, length-read);
 }
 memcpy(data + read, b.Data + read_offset, read_length);
 read += read_length;
 }
 return read;
}

// Allocate free block --------------------------------------------------------------
ssize_t FileSystem::allocate_free_block() {
    int block = -1;
    for (unsigned int i = 0; i < blocks; i++) {
        if (block_bitmap[i]) {
            block_bitmap[i] = 0;
            block = i;
            break;
        }
    }

    // need to zero data block if we're allocating one
    if (block != -1) {
        char data[disk->BLOCK_SIZE];
        memset(data,0,disk->BLOCK_SIZE);
        disk->write(block,(char*)data);
    }

    return block;
    return 0;
}


ssize_t FileSystem::write(size_t inumber, char *data, size_t length, size_t offset) {
 // Load inode
 Inode inode;
 if (!load_inode(inumber, &inode) || offset > inode.Size) {
 return -1;
 }

 size_t MAX_FILE_SIZE = disk->BLOCK_SIZE * (POINTERS_PER_INODE*POINTERS_PER_BLOCK);

 // Adjust length
 length = std::min(length, MAX_FILE_SIZE-offset);
 
 uint32_t start_block = offset / disk->BLOCK_SIZE;
 Block indirect;
 bool read_indirect = false;

 bool modified_inode = false;
 bool modified_indirect = false;

 // Write block and copy data
 size_t written = 0;
 for (uint32_t block_num = start_block; written < length && block_num < POINTERS_PER_INODE + POINTERS_PER_BLOCK; block_num++) {
 
 // figure out which block we're reading
 size_t block_to_write;
 if (block_num < POINTERS_PER_INODE) {
 // Allocate block if necessary
 if (inode.Direct[block_num] == 0) {
 ssize_t allocated_block = allocate_free_block();
 if (allocated_block == -1) {
 break;
 }
 inode.Direct[block_num] = allocated_block;
 modified_inode = true;
 }
 block_to_write = inode.Direct[block_num];
 } else { // Indirect block
 // Allocate indirect block if necessary
 if (inode.Indirect == 0) {
 ssize_t allocated_block = allocate_free_block();
 if (allocated_block == -1) {
 return written;
 }
 inode.Indirect = allocated_block;
 modified_indirect = true;
 }

 // Read indirect block if hasn't been read yet
 if (!read_indirect) {
 disk->read(inode.Indirect,indirect.Data);
 read_indirect = true;
 }

 // Allocate block if necessary
 if (indirect.Pointers[block_num - POINTERS_PER_INODE] == 0) {
 ssize_t allocated_block = allocate_free_block();
 if (allocated_block == -1) {
 break;
 }
 indirect.Pointers[block_num - POINTERS_PER_INODE] = allocated_block;
 modified_indirect = true;
 }
 block_to_write = indirect.Pointers[block_num-POINTERS_PER_INODE];
 }

 //get the block -- from either direct or indirect
 size_t write_offset;
 size_t write_length;

 // if it's the first block written, have to start from an offset
 // and write either until the end of the block, or the whole request
 if (written == 0) {
 write_offset = offset % disk->BLOCK_SIZE;
 write_length = std::min(disk->BLOCK_SIZE - write_offset, length);
 } else {
 // otherwise, start from the beginning, and write
 // either the whole block or the rest of the request
 write_offset = 0;
 write_length = std::min(disk->BLOCK_SIZE-0, length-written);
 }

 char write_buffer[disk->BLOCK_SIZE];

 // if we're not writing the whole block, need to copy what's there
 if (write_length < disk->BLOCK_SIZE) {
 disk->read(block_to_write,(char*)write_buffer);
 }

 // copy into buffer
 memcpy(write_buffer + write_offset, data + written, write_length);
 disk->write(block_to_write,(char*)write_buffer);
 written += write_length;
 }

 // update inode size
 uint32_t new_size = std::max((size_t)inode.Size, written + offset);
 if (new_size != inode.Size) {
 inode.Size = new_size;
 modified_inode = true;
 }

 // save inode and indirect if necessary
 if (modified_inode) {
 save_inode(inumber,&inode);
 }
 
 if (modified_indirect) {
 disk->write(inode.Indirect,indirect.Data);
 }

 return written;
}
bool FileSystem::load_inode(size_t inumber, Inode *node) {
    size_t block_number = 1 + (inumber / INODES_PER_BLOCK);
    size_t inode_offset = inumber % INODES_PER_BLOCK;

    if (inumber >=inodes) {
        return false;
    }

    Block block;
    disk->read(block_number,block.Data);

    *node = block.Inodes[inode_offset];

    return true;
}

bool FileSystem::save_inode(size_t inumber, Inode *node) {

    size_t block_number = 1 + inumber / INODES_PER_BLOCK;
    size_t inode_offset = inumber % INODES_PER_BLOCK;

    if (inumber >= inodes) {
        return false;
    }

    Block block;
    disk->read(block_number,block.Data);
    block.Inodes[inode_offset] = *node;
    disk->write(block_number,block.Data);

    return true;
}

