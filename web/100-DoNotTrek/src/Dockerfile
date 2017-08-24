# Import Python runtime and set up working directory
FROM python:2.7-slim
WORKDIR /
#ADD . /
RUN apt-get update -y
RUN apt-get install -y python-pip
RUN pip install flask
ADD dnt.py /dnt.py
ADD static /static
ADD templates /templates
ADD flag /flag

# Open port 5000 for serving the webpage, mapped to 80 by container engine
EXPOSE 5000

# Run app.py when the container launches
CMD ["su","-s","/bin/sh","nobody","-c","python dnt.py"]
