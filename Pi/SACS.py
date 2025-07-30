import serial
import cv2 as cv
from time import sleep
from telegram import Bot
from telegram.ext import Updater, CommandHandler

# variables
chat_id = "-4818602009"
path = "/home/chestnut/.local/share/.telegram_bot_token"
photo = "/home/chestnut/code/images/"
port = "/dev/ttyACM0"
baudrate = 115200
time_out = 1.0
threshold = 5 # seconds
counter = 0 # image counter

def photo_handler(update, context):
    with open(f"{photo}{image_name}","rb") as image_file:
        print("Sending photo to telegram")
        last_image_taken = image_file.read().rstrip()
        context.bot.send_photo(chat_id=update.effective_chat.id,photo=last_image_taken, caption=f"Send /open or /deny")

# allow access
def open_handler(update, context):
    cmd = update.message.text[1:]
    cmd = cmd + "\n"
    arduino.write(cmd.encode("utf-8"))
    bot.send_message(chat_id=chat_id,text="Allowing access")

# deny access
def deny_handler(update, context):
    cmd = update.message.text[1:]
    cmd = cmd + "\n"
    arduino.write(cmd.encode("utf-8"))
    bot.send_message(chat_id=chat_id,text="Denying access")
    
# loads the telegram token
with open(path, "r") as file:
    token = file.readline().rstrip()

# creates an object of the libraries created
bot = Bot(token=token)
updater = Updater(token=token)
dispatcher = updater.dispatcher

# handler
dispatcher.add_handler(CommandHandler("photo", photo_handler))
dispatcher.add_handler(CommandHandler("open", open_handler))
dispatcher.add_handler(CommandHandler("deny", deny_handler))
updater.start_polling()

while True: # Checks if arduino is connected
    try:
        arduino = serial.Serial(port, baudrate, timeout=time_out)
        bot.send_message(chat_id=chat_id,text="Arduino connected")
        print("Serial connected successfully")
        break
    
    except serial.SerialException:
        print("Failed to connect. Trying again...")
        sleep(2)
        
sleep(2)
arduino.reset_input_buffer()
print("Serial ok")
    
try:
    while True:
        sleep(0.01)   
        if arduino.in_waiting > 0:
            # checks if button is pressed
            cmd = arduino.readline().rstrip().decode("utf-8")
                
            # sends the last picture take to telegram when button is pressed    
            if cmd == "button_pressed":
                cam = cv.VideoCapture(0)
                _ , frame = cam.read()
                image_name = f"{counter}.png" # names the picture taken
                cv.imwrite(f"{photo}{image_name}",frame) # saves the photo
                cam.release()
                cv.destroyAllWindows()
                counter += 1

                # loads the last picture taken
                with open(f"{photo}{counter-1}.png","rb") as image_file:
                    last_image_taken = image_file.read().rstrip()
                    print("Sending photo to telegram")
                    
                bot.send_photo(chat_id=chat_id, photo=last_image_taken, caption=f"Send /open or /deny")
            

except KeyboardInterrupt: # executes if there is an interrupt
    bot.send_message(chat_id=chat_id,text="Arduino disconnected")
    print("Closing Serial Communication. Wait a few seconds")
    arduino.close()
    updater.stop()
    print("Serial Communication Closed.")
