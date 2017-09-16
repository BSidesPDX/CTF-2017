# Import Python runtime and set up working directory
FROM python:2.7-slim
WORKDIR /
#ADD . /
RUN dpkg --add-architecture i386
RUN apt-get update -y
RUN apt-get install -y xinetd libc6:i386 binutils:i386
RUN echo "movon 35264/tcp" >> /etc/services
ADD movon.service /etc/xinetd.d/movon
ADD movon /movon
ADD flag /flag

# Open port 5000 for serving the webpage, mapped to 80 by container engine
EXPOSE 35264

# Run app.py when the container launches
CMD ["xinetd","-dontfork"]
