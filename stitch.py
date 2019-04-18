# import the necessary packages
from panorama import Stitcher
import argparse
import imutils
import cv2
 
# construct the argument parse and parse the arguments
#ap = argparse.ArgumentParser()
#ap.add_argument("-f", "--first", required=True,
#	help="path to the first image")
#ap.add_argument("-s", "--second", required=True,
#	help="path to the second image")
#args = vars(ap.parse_args())
cap1 = cv2.VideoCapture(1)
cap2 = cv2.VideoCapture(2)
warp = False
showMatches = True
#img = cv2.imread("sam1.jpg", 1)
#img2 = cv2.imread("sam2.jpg",1)

while(True):

    # load the two images and resize them to have a width of 400 pixels
    # (for faster processing)
    imageA = cap1.read()[1]
    imageB = cap2.read()[1]
    imageA = cv2.resize(imageA, (480, 640))
    imageB = cv2.resize(imageB, (480, 640))
 
# stitch the images together to create a panorama
    stitcher = Stitcher()
    if showMatches:
        (result, vis) = stitcher.stitch(imageA, imageB, warp, showMatches)
    else: 
        result = stitcher.stitch(imageA, imageB, warp, showMatches) 
# show the images
    #cv2.imshow("Image A", imageA)
    #cv2.imshow("Image B", imageB)
    result = cv2.resize(result, (480*2, 640))
    if showMatches:
        cv2.imshow("Keypoint Matches", vis)
    cv2.imshow("Result", result)
    c = cv2.waitKey(1)
    if c == 27:
        break
cap1.release()
cap2.release()
cv2.destroyAllWindows()
