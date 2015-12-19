# -*- coding: utf-8 -*-
import pymorphy2

class FilterMessages:
    def __init__(self):
        self.morph = pymorphy2.MorphAnalyzer()

    def __call__(self, msg):
        body = msg.body.lower()
        if not self._inspection_of_phrases_off(body):
            return False
        if self._inspection_of_phrases_on(body):
            return True
        if self._imperative_mood(body):
            return True

    def _imperative_mood(self, body):
        for word in body.split():
            p = self.morph.parse(word)[0]
            if 'impr' in p.tag:
                return True
        return False

    def _inspection_of_phrases_off(self, body):
        if u'не отвечайте на это письмо' in body:
            return False
        return True

    def _inspection_of_phrases_on(self, body):
        if u'?' in body:
            return True
        return False
