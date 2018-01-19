import datetime
#import pytz #python -m pip install pytz
#dt = datetime.datetime(2018,7,13,9,30,50)
#dt_now = datetime.datetime.now(2018,7,13,9,30,5000, tz=pytz.UTC)

dt_d = datetime.date.today()
dt_t = datetime.time().hour
dt_dt = datetime.datetime.today()

print(dt_d)
print(dt_t.isoformat)
print(dt_dt
