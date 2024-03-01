import requests

game_adress = 'http://127.0.0.1:5042'

def get_info():
    r = requests.get(game_adress + '/board')
    print(r.text)

    r = requests.get(game_adress + '/status')
    print(r.text)

# Note that cell numbers start from 1, not from 0 !
def make_move(cell, player):
    payload = {'filed': str(cell-1), 'player': str(player)}
    r = requests.get(game_adress + '/make_move', params=payload)
    print(r.text)

r = requests.get(game_adress + '/start_game')
print(r.text)

make_move(5, 1)
make_move(5, 1)
make_move(5, 2)
make_move(2, 2)
get_info()

make_move(1, 1)
make_move(9, 2)
make_move(4, 1)
get_info()

make_move(4, 2)
make_move(7, 2)
make_move(6, 2)
get_info()

make_move(6, 1)
get_info()