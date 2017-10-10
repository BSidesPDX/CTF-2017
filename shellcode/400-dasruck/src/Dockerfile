FROM python:2.7-slim
WORKDIR /
RUN apt-get update 
RUN apt-get install -y xinetd
RUN echo "dasruck 5050/tcp" >> /etc/services
ADD dasruck.service /etc/xinetd.d/dasruck
ADD dasruck /dasruck
ADD flag /flag

EXPOSE 5050

CMD ["xinetd","-dontfork"]
