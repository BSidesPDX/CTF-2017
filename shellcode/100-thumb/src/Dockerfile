# Import Python runtime and set up working directory
FROM python:2.7-slim
WORKDIR /
#ADD . /
RUN apt-get update -y
RUN apt-get install -y vim strace xinetd qemu binfmt-support qemu-user-static
RUN echo "thumb 31337/tcp" >> /etc/services
ADD thumb.service /etc/xinetd.d/thumb
ADD thumb /thumb
ADD flag /flag

# Open port 5000 for serving the webpage, mapped to 80 by container engine
EXPOSE 31337

# Run app.py when the container launches
CMD ["xinetd","-dontfork"]
