FROM ubuntu:xenial

run apt-get update
run apt-get install -y xinetd build-essential gcc-multilib vim-common gdb
run apt-get clean

# Add files to container
WORKDIR /opt/cookie
COPY flag /
COPY cookie /opt/cookie/cookie
RUN ls

RUN mkdir -p /var/run/cookie

EXPOSE 53000
CMD ["gdb", "-ex", "run", "./cookie"]  
