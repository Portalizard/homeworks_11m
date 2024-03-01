from flask import Flask
from flask import request
import re

app = Flask(__name__)

deck = []
move_order = 1
p1_move_cnt = 0
p2_move_cnt = 0

@app.route('/')
def hello_world(): 
    return 'Hello tic-tac-toe game!'

@app.route('/start_game')
def start_game():
    global deck
    global move_order
    global p1_move_cnt
    global p2_move_cnt

    deck = ['.' for i in range(9)]
    move_order = 1
    p1_move_cnt = 0
    p2_move_cnt = 0
    return 'Game started'

@app.route('/make_move')
def make_move():
    global deck
    global move_order
    global p1_move_cnt
    global p2_move_cnt

    if request.args['player'] == '1':
        if move_order != 1:
            return 'P1, it is not your turn yet, be patient!'
        if deck[int(request.args['filed'])] != '.':
            return 'P1, watch your moves!'
        
        deck[int(request.args['filed'])] = 'x'
        move_order = 2
        p1_move_cnt += 1
        return 'P1 made a move'
    
    if request.args['player'] == '2':
        if move_order != 2:
            return 'P2, it is not your turn yet, be patient!'
        if deck[int(request.args['filed'])] != '.':
            return 'P2, watch your moves!'
        
        deck[int(request.args['filed'])] = 'o'
        move_order = 1
        p2_move_cnt += 1
        return 'P2 made a move'
    
    return 'Move made?'

@app.route('/board')
def board():
    global deck
    global move_order
    global p1_move_cnt
    global p2_move_cnt

    s = deck2str()
    return s[0:3] + "\n" + s[3:6] + "\n" + s[6:9]

# Additional info on number of moves is returned only if status is 'game in progress',
# because move ordering is implemented, so any win is guaranteed to be fair
@app.route('/status')
def status():
    global deck
    global move_order
    global p1_move_cnt
    global p2_move_cnt

    s = deck2str()

    # Witchcraft from the Internet
    x = re.search(r"(x)(..\1..\1|...\1...\1|.\1.\1..$|\1\1(...)*$)", s)
    o = re.search(r"(o)(..\1..\1|...\1...\1|.\1.\1..$|\1\1(...)*$)", s)

    if x and o:
        return 'Hmm... seems like a draw. Are you two cheating?!'
    if x:
        return 'Player 1 won!'
    if o:
        return 'Player 2 won!'

    # Yes, it will say 'moveS' even if it is only 1 move.
    # And yes, i do not really care, it's 22:52
    return 'Game in progress: p1 - ' + str(p1_move_cnt) + \
        ' moves , p2 - ' + str(p2_move_cnt) + ' moves'


def deck2str():
    global deck
    global move_order
    global p1_move_cnt
    global p2_move_cnt

    s = ''
    for i in range(9):
        s += deck[i]
    return s

if __name__ == '__main__':
    app.run(port=5042)