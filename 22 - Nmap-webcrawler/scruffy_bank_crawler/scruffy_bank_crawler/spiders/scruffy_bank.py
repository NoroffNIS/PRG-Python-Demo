# -*- coding: utf-8 -*-
import scrapy


class ScruffyBankSpider(scrapy.Spider):
    name = 'scruffy_bank'
    allowed_domains = ['http://172.24.3.54/']
    start_urls = ['http://http://172.24.3.54//']

    def parse(self, response):
        pass
