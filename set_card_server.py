from flask import Flask
from flask import request
from flask import send_file
from flask import render_template
import requests
import re

app = Flask(__name__, template_folder='html')
month = 0
day = 0

@app.route('/test', methods=['GET'])
def hello_world():
    r = requests.get('https://www.setgame.com/set/puzzle')

    text = r.text
    s1 = r'[a-z/](.\d)\.png'
    x = re.findall(s1, text)
    if len(x) != 12:
        return 'Something went wrong', 500

    card_number = month * day % 12
    card_type = x[card_number]
    if card_type[0] == '/':
        card_type = card_type[1:]
    card_type = int(card_type)

    print(card_type)
    return 'test'

@app.route('/daily_card', methods=['GET'])
def daily_card():
    r = requests.get('https://www.setgame.com/set/puzzle')

    text = r.text
    s1 = r'[a-z/](.\d)\.png'
    x = re.findall(s1, text)
    if len(x) != 12:
        return 'Something went wrong', 500

    card_number = month * day % 12
    card_type = x[card_number]
    if card_type[0] == '/':
        card_type = card_type[1:]
    card_type = int(card_type)

    return render_template('card.html', n = str(card_type))

@app.route('/set_my_date', methods=['GET'])
def set_date():
    global month
    global day
    month = int(request.args['month'])
    day = int(request.args['day'])
    return send_file('html/date.html')

@app.route('/res/cow.png', methods=['GET'])
def cow():
    return send_file('res/cow.png')

if __name__ == '__main__':
    app.run(port=5042)

"""
TEMPLATES
http://127.0.0.1:5042/set_my_date?day=1&month=1
"""