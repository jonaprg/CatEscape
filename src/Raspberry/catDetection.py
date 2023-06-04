import cv2
import sys
import smbus2 as smbus
import time

# Slave Addresses
I2C_SLAVE_ADDRESS = 11

# define a vi' deo capture object
face_cascade = cv2.CascadeClassifier('haarcascade_frontalcatface_extended.xml')
cap = cv2.VideoCapture(0)

def notify_cat_detected():
    try:
        I2Cbus = smbus.SMBus(1)
        with smbus.SMBus(1) as I2Cbus:
            I2Cbus.write_i2c_block_data(I2C_SLAVE_ADDRESS, 0x00,[1])
            time.sleep(0.5)
    except:
        pass

while(True):
    # Capture the video frame
    # by frame
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale(frame, scaleFactor=1.3, minNeighbors=5, minSize=(75,75))

    for (x, y, w, h) in faces:
        cv2.rectangle(frame,(x,y),(x+w,y+h), (0,255,0), 2)
        print("Cat Detected")
        notify_cat_detected()
        

    # cv2.imshow('Cat Detector', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()

cv2.destroyAllWindows()
# After the loop release the cap object
vid.release()
# Destroy all the windows
cv2.destroyAllWindows()
