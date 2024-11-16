FROM ubuntu:22.04

# User and group config
ARG uid
ARG gid
ARG user
ARG group

RUN groupadd -g ${gid} ${group} || true
RUN useradd -l -u ${uid} -g ${group} -m ${user} || true


ENV TERM=xterm
ENV DEBIAN_FRONTEND=noninteractive


# Update
RUN apt-get update

# Install dependencies

RUN apt-get install -y g++
RUN apt-get install -y tzdata
RUN apt-get upgrade -y
RUN apt-get install -y cmake
RUN apt-get install -y libgtest-dev
RUN apt-get install -y vim make git libgtk2.0-dev pkg-config libopencv-dev

# Install GTest
RUN cd /usr/src/gtest && cmake CMakeLists.txt && make && cp lib/*.a /usr/lib

# Clean up
RUN apt-get clean