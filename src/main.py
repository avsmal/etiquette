# -*- coding: utf-8 -*-
import accounts
from applet import Applet
from MailDB import MailDB
from server import Server

recently = 5
long = 15
long_long = 1E9
dow_t = 1E9
# 0 <= t <= recently Письмо пришло недавно
# recently <= t <= long Письмо пришло давно
# long <= t <= long_long Письмо пришло очень давно
# dow_t с какой периодичностью мы подключаемся к серверу за письмами


if __name__ == '__main__':
    setting = accounts.Setting('config.xml')
    server = Server('config.xml')

    recently = int(setting.getString('ddd.time.recently'))
    long = int(setting.getString('ddd.time.long'))
    long_long = int(setting.getString('ddd.time.long_long'))
    dow_t = int(setting.getString('ddd.time.download_time'))

    db = MailDB(recently, long, long_long, dow_t, server)
    ap = Applet(data_base=db)
    ap.show()
