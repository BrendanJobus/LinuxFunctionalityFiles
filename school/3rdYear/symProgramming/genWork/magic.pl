:- dynamic(witch/1).
hasWand(harry).
quidditchPlayer(harry).
wizard(ron).
wizard(X) :- hasBroom(X), hasWand(X).
hasBroom(X):- quidditchPlayer(X).
