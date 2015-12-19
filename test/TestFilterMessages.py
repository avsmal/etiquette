# -*- coding: utf-8 -*-
import datetime
from FilterMessages import FilterMessages
from server import Message


class TestFilterMessages:
    def test_sample_1(self):
        # '['sender', 'to', 'date', 'subject', 'body']'
        msg = Message('email_sender', 'email_to', datetime.datetime.now(),
                      'Привет',
                      u'Василий! Отправьте пожалуйста мне кое что.')
        filter_msg = FilterMessages()
        assert filter_msg(msg)

    def test_sample_2(self):
        msg = Message('email_sender', 'email_to', datetime.datetime.now(),
                      'Привет',
                      u'Василий! Когда будет обед?')
        filter_msg = FilterMessages()
        assert filter_msg(msg)

    def test_sample_3(self):
        msg = Message('email_sender', 'email_to', datetime.datetime.now(),
                      'Привет',
                      u'Василий! Ваш заказ доставлен на склад!')
        filter_msg = FilterMessages()
        assert not filter_msg(msg)

    def test_sample_4(self):
        msg = Message('email_sender', 'email_to', datetime.datetime.now(),
                      'Привет',
                      u'''Василий! Вы можете подключить новую услугу нашего
                      банка, для этого отправьте смс на номер 7777 с текстом 2323.
                      \n\n\n Этот электронный адрес не может принимать сообщения.
                       \n\n\nПожалуйста, не отвечайте на это письмо.''')
        filter_msg = FilterMessages()
        assert not filter_msg(msg)
