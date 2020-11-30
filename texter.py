import RPi.GPIO as GPIO
import time
import os
from twilio.rest import Client

# Need to update / fix detection bugs still

def get_twilio_client():
    account_sid = os.environ['TWILIO_ACCOUNT_SID']
    auth_token = os.environ['TWILIO_AUTH_TOKEN']
    client = Client(account_sid, auth_token)

def send_text():
    client = get_twilio_client()
    TWILIO_NUMBER = None
    MY_NUMBER = None
    message = client.messages.create(
                        body="Water needed.",
                        from_=TWILIO_NUMBER,
                        to=MY_NUMBER
                    )
    time.sleep(60)


def check_moist(pin):
    if GPIO.input(pin):
        send_text(get_twilio_client())

GPIO.setmode(GPIO.BCM)
PIN = 17
GPIO.setup(PIN, GPIO.IN)

GPIO.add_event_detect(PIN, GPIO.BOTH, bouncetime=300)
GPIO.add_event_callback(PIN, check_moist)

while True:
    time.sleep(1)
