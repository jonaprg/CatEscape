import cv2

# define a vi' deo capture object
face_cascade = cv2.CascadeClassifier('haarscascade_frontalcatface_extended.xml')
cap = cv2.VideoCaptura(0)

while(True):

    # Capture the video frame
    # by frame
    ret, frame = cap.read()

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    for (x, y, w, h) in faces:
        cv2.rectangle(frame,(x,y),(x+w,y+h), (255,255,0), 2)
        roi_gray=gray[y:y + h,x:x + w]
        roi_color = img[y:y + h, x:x + w]
        print("Cat Detected")

    cv2.imshow('Cat Detector', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()

cv2.destroyAllWindows()
# After the loop release the cap object
vid.release()
# Destroy all the windows
cv2.destroyAllWindows()
