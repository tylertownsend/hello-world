# Use an official base image
FROM ubuntu:latest

# Install necessary packages
RUN apt-get update && apt-get install -y \
    build-essential \
    nasm \
    xorriso \
    grub-pc-bin \
    grub-common
    
VOLUME /root/env
WORKDIR /root/env

# # Copy your C++ project into the Docker image
# COPY .. /home/src/os

# # Set the working directory
# WORKDIR /home/src/os

# # Command to build your project
# CMD ["make", "all"]
