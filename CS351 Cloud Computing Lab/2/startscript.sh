#cloud-boothook
#!/bin/bash

sudo yum update -y
sudo yum install httpd -y
service httpd start
wget https://awsbucketboi.s3.amazonaws.com/index.html
sudo cp index.html /var/www/html/index.html