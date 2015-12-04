from applet import Applet
from MailDB import MailDB
from server import Server

if __name__ == '__main__':
    server = Server('config.xml')
    db = MailDB(10, 15, 1E9, 1E9, server)
    ap = Applet(data_base=db)
    ap.show()
