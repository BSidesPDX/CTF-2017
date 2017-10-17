# Import Python runtime and set up working directory
FROM python:2.7-slim
WORKDIR /
#ADD . /

ADD rfcsearch /
ADD index.txt /
RUN mkdir rfc
ADD rfcs /rfc
ADD flag /

# Open port 5001 for serving the webpage, mapped to 80 by container engine
EXPOSE 5001

# Run app.py when the container launches
CMD ["/rfcsearch"]

