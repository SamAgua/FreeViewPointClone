import numpy as np
import imutils
import cv2
np.set_printoptions(threshold=np.inf)

class Stitcher:
    def __init__(self):
    # determine if we are using OpenCV v3.X
        self.isv3 = imutils.is_cv3()

    def stitch(self, imageA, imageB, warp, showMatches, ratio=0.75, reprojThresh=10.0):
    # unpack the images, then detect keypoints and extract
    # local invariant descriptors from them
    #(imageB, imageA) = images
        (kpsA, featuresA) = self.detectAndDescribe(imageA)
        (kpsB, featuresB) = self.detectAndDescribe(imageB)

    # match features between the two images
        M = self.matchKeypoints(kpsA, kpsB,
            featuresA, featuresB, ratio, reprojThresh)

    # if the match is None, then there aren't enough matched
    # keypoints to create a panorama
        if M is None:
            return None

    # otherwise, apply a perspective warp to stitch the images
    # together
        (matches, H, status) = M
    # check to see if the keypoint matches should be visualized
        if showMatches:
            (vis, maxA, minB) = self.drawMatches(imageA, imageB, kpsA, kpsB, matches,
            status)

        # return a tuple of the stitched image and the
        # visualization
            #return (result, vis)
            if warp:
                result = np.zeros((imageB.shape[0], imageA.shape[1] + imageB.shape[1],
                           3), dtype="uint8")
                Bresult = cv2.warpPerspective(imageB, H,
            (imageB.shape[1], imageB.shape[0]), cv2.INTER_NEAREST)
                
                result[0:imageA.shape[0], 0:imageA.shape[1]] = imageA
                result[0:imageA.shape[0],imageA.shape[1]: ] = Bresult
                return (result, vis)

            result = np.zeros((imageB.shape[0], maxA + imageB.shape[1]-minB,
                           3), dtype="uint8")
            result[0:imageA.shape[0], 0:maxA] = imageA[0:imageA.shape[0], 0:maxA]
            result[0:imageA.shape[0],maxA: ] = imageB[0:imageB.shape[0],
                                                                  minB: ]
            return (result, vis)
        else:
            (maxA, minB) = self.findMaxMinPts(imageA, imageB, kpsA, kpsB, matches,
                                              status)
            if warp:
                result = np.zeros((imageB.shape[0], imageA.shape[1] + imageB.shape[1],
                           3), dtype="uint8")
    # create warped imgB to be stitched onto imgA
                Bresult = cv2.warpPerspective(imageB, H,
            (imageB.shape[1], imageB.shape[0]), cv2.INTER_NEAREST)
                
                result[0:imageA.shape[0], 0:imageA.shape[1]] = imageA
                result[0:imageA.shape[0],imageA.shape[1]: ] = Bresult
                return (result)
    # create 3d array to hold panoramic view
            result = np.zeros((imageB.shape[0], maxA + imageB.shape[1]-minB,
                           3), dtype="uint8")
            result[0:imageA.shape[0], 0:maxA] = imageA[0:imageA.shape[0], 0:maxA]
            result[0:imageA.shape[0],maxA: ] = imageB[0:imageB.shape[0],
                                                                  minB: ]
            return (result)
        
    
        
    # Add imgA to result, then add warped imgB
          

    

    # return the stitched image

    def detectAndDescribe(self, image):
    # convert the image to grayscale
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # check to see if we are using OpenCV 3.X
        if self.isv3:
        # detect and extract features from the image
        #SIFT Algorithm
            #descriptor = cv2.xfeatures2d.SIFT_create()
        #SURF Algorithm
            descriptor = cv2.xfeatures2d.SURF_create()# 400 is hesian threshold, optimum values should be around 300-500
        
            (kps, features) = descriptor.detectAndCompute(image, None)
          

        # convert the keypoints from KeyPoint objects to NumPy
        # arrays
        kps = np.float32([kp.pt for kp in kps])

        # return a tuple of keypoints and features
        #print("features",features)
        #print(kps);
        return (kps, features)

    def matchKeypoints(self, kpsA, kpsB, featuresA, featuresB,
        ratio, reprojThresh):
    # compute the raw matches and initialize the list of actual
    # matches
        matcher = cv2.DescriptorMatcher_create("FlannBased")
        rawMatches = matcher.knnMatch(featuresA, featuresB, 2)
        matches = []

    # loop over the raw matches
        for m in rawMatches:
        # ensure the distance is within a certain ratio of each
        # other (i.e. Lowe's ratio test)
            if len(m) == 2 and m[0].distance < m[1].distance * ratio:
                matches.append((m[0].trainIdx, m[0].queryIdx))
        print(len(matches))

    # computing a homography requires at least 4 matches
        if len(matches) > 4:
        # construct the two sets of points
            ptsA = np.float32([kpsA[i] for (_, i) in matches])
            ptsB = np.float32([kpsB[i] for (i, _) in matches])

        # compute the homography between the two sets of points
            (H, status) = cv2.findHomography(ptsA, ptsB, cv2.RANSAC,
                reprojThresh)

        # return the matches along with the homograpy matrix
        # and status of each matched point
            return (matches, H, status)

    # otherwise, no homograpy could be computed
        return None

    def drawMatches(self, imageA, imageB, kpsA, kpsB, matches, status):
    # initialize the output visualization image
        (hA, wA) = imageA.shape[:2]
        (hB, wB) = imageB.shape[:2]
        vis = np.zeros((max(hA, hB), wA + wB, 3), dtype="uint8")
        vis[0:hA, 0:wA] = imageA
        vis[0:hB, wA:] = imageB

    # loop over the matches
        maxA = 0
        minB = wB
        for ((trainIdx, queryIdx), s) in zip(matches, status):
        # only process the match if the keypoint was successfully
        # matched
            if s == 1:
            # draw the match
                ptA = (int(kpsA[queryIdx][0]), int(kpsA[queryIdx][1]))
                ptB = (int(kpsB[trainIdx][0]) + wA, int(kpsB[trainIdx][1]))
                if (int(kpsA[queryIdx][0]) > maxA):
                    maxA = int(kpsA[queryIdx][0])
                if (int(kpsB[trainIdx][0]) < minB):
                    minB = int(kpsB[trainIdx][0])
                cv2.line(vis, ptA, ptB, (0, 255, 0), 1)

    # return the visualization
        return (vis, maxA, minB)
    
    def findMaxMinPts(self, imageA, imageB, kpsA, kpsB, matches, status):
    # initialize the output visualization image
        (hA, wA) = imageA.shape[:2]
        (hB, wB) = imageB.shape[:2]
        #vis = np.zeros((max(hA, hB), wA + wB, 3), dtype="uint8")
        #vis[0:hA, 0:wA] = imageA
        #vis[0:hB, wA:] = imageB

    # loop over the matches
        maxA = 0
        maxB = 0
        for ((trainIdx, queryIdx), s) in zip(matches, status):
        # only process the match if the keypoint was successfully
        # matched
            if s == 1:
            # draw the match
                ptA = (int(kpsA[queryIdx][0]), int(kpsA[queryIdx][1]))
                ptB = (int(kpsB[trainIdx][0]) + wA, int(kpsB[trainIdx][1]))
                if (int(kpsA[queryIdx][0]) > maxA):
                    maxA = int(kpsA[queryIdx][0])
                if (int(kpsB[trainIdx][0]) > maxB):
                    maxB = int(kpsB[trainIdx][0])
                #cv2.line(vis, ptA, ptB, (0, 255, 0), 1)

    # return the visualization
        return (maxA, maxB)
