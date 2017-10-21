FROM ubuntu:xenial

run apt update
run apt install build-essential gcc-multilib g++-multilib git xinetd telnetd -y
run apt install libncurses5 lib32ncurses5 lib32ncurses5-dev libncurses5-dev -y
run apt clean

# Add files to container
WORKDIR /opt/2048
ADD 2048.service /etc/xinetd.d/2048
ADD flag /

# Create a user for the container
RUN useradd -ms /bin/bash 2048
RUN chown -R 2048:2048 /opt/2048
RUN chmod -R 775 /opt/2048/
RUN chmod -R 666 /opt/2048/flag

# Make and run
ADD 2k48/2k48 2k48
RUN echo "2048 2048/tcp" >> /etc/services
EXPOSE 2048

CMD ["xinetd", "-dontfork"]
