# author : Loodoor
# all rights reserved

# PLEASE DO NOT DELETE THIS FILE
Unamed.loadImage("assets/gui/pnj/bubble.png", "balloon")

def display_ballon(textid):
    if Unamed.getCurrentViewId() == 1:
        Unamed.displayWithView("balloon", 10, 530)
        Unamed.writeText(textid)