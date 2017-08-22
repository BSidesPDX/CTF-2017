FROM ubuntu:xenial

run apt update
run apt install build-essential gcc-multilib -y
run apt clean

# Add files to container
WORKDIR /opt/leek
COPY makefile /opt/leek/
COPY flag /opt/leek/
COPY leek.c /opt/leek/

# Create a user for the container
RUN useradd -ms /bin/bash leek
RUN chown -R leek:leek /opt/leek
RUN chmod -R 775 /opt/leek
RUN chmod 700 /opt/leek/flag

# Make and run
USER leek
RUN make
EXPOSE 2007
CMD ["./leek", "&"]
