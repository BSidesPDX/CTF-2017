FROM ubuntu:xenial

run apt update
run apt install build-essential gcc-multilib g++-multilib git xinetd telnetd -y
run apt install libncurses5 lib32ncurses5 lib32ncurses5-dev libncurses5-dev -y
run apt clean

# Add files to container
WORKDIR /opt/2048
ADD flag /opt/2048/
ADD 2048.patch /opt/2048/
ADD 2048.service /etc/xinetd.d/2048

# Create a user for the container
RUN useradd -ms /bin/bash 2048
RUN chown -R 2048:2048 /opt/2048
RUN chmod -R 775 /opt/2048

# Make and run
RUN git clone https://github.com/sc0ty/2k48
WORKDIR 2k48
RUN git checkout 7ac0035162f7014b7542ff13a2e7b22123bae662
RUN git apply ../2048.patch
ADD highscore.cpp .
ADD highscore.h .
RUN make DAEMON=1
run echo "2048 2048/tcp" >> /etc/services
EXPOSE 2048

CMD ["xinetd", "-dontfork"]
