#!/usr/bin/python
from flask import Flask
from flask import render_template
from flask import request
app = Flask(__name__, static_url_path='/static')

@app.route('/')
def index():
    try:
        dnt = eval(request.headers['DNT'])
    except KeyError as e:
        dnt = 'OFF'
    return render_template('dnt.html', dnt=dnt)

app.run(host='0.0.0.0')
