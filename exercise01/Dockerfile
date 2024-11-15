FROM ubuntu:20.04

# User and group config
ARG uid
ARG gid
ARG user
ARG group

RUN groupadd -g ${gid} ${group} || true
RUN useradd -l -u ${uid} -g ${group} -m ${user} || true

# Update
RUN apt-get update

# Install dependencies
RUN apt-get install -y g++
RUN apt-get install -y cmake
RUN apt-get install -y libgtest-dev

# Install GTest
RUN cd /usr/src/gtest && cmake CMakeLists.txt && make && cp lib/*.a /usr/lib