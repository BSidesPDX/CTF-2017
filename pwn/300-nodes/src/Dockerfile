FROM ubuntu:xenial

run apt-get update
run apt-get install build-essential gcc-multilib xinetd -y
run apt-get clean

# Add files to container
WORKDIR /opt/
ADD flag /
ADD nodes.service /etc/xinetd.d/nodes
ADD nodes /opt/nodes

# Make and run
run echo "nodes 4321/tcp" >> /etc/services
EXPOSE 4321

CMD ["xinetd", "-dontfork"]
