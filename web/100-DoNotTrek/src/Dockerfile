# Import Python runtime and set up working directory
FROM python:2.7-slim
WORKDIR /
RUN apt-get update
RUN apt-get install -y python-pip
RUN pip install flask
ADD dnt.py /dnt.py
ADD static /static
ADD templates /templates
ADD flag /flag

EXPOSE 5000

# Run app.py when the container launches
CMD ["su","-s","/bin/sh","nobody","-c","python dnt.py"]
