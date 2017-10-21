FROM ubuntu:xenial

run apt-get update
run apt-get install build-essential gcc-multilib xinetd -y
run apt-get clean

# Add files to container
WORKDIR /opt/leek
COPY flag /
COPY leek /opt/leek/
COPY leek.service /etc/xinetd.d/nodes

# Make and run
RUN echo "leek 2007/tcp" >> /etc/services
EXPOSE 2007

CMD ["xinetd", "-dontfork"]
