FROM ubuntu:xenial

run apt-get update -y
run apt-get install build-essential gcc-multilib xinetd -y
run apt-get clean

# Add files to container
WORKDIR /opt/
ADD flag /opt/
ADD nodes.c /opt/
ADD Makefile /opt/
ADD nodes.service /etc/xinetd.d/nodes

# Make and run
RUN make
run echo "nodes 4321/tcp" >> /etc/services
EXPOSE 4321

CMD ["xinetd", "-dontfork"]
