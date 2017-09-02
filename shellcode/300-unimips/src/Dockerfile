# Import Python runtime and set up working directory
FROM python:2.7-slim
WORKDIR /
#ADD . /
RUN apt-get update -y
RUN apt-get install -y vim strace xinetd qemu binfmt-support qemu-user-static
RUN echo "unimips 41414/tcp" >> /etc/services
ADD unimips.service /etc/xinetd.d/unimips
ADD unimips /unimips
ADD flag /flag

# Open port 5000 for serving the webpage, mapped to 80 by container engine
EXPOSE 41414

# Run app.py when the container launches
CMD ["xinetd","-dontfork"]
