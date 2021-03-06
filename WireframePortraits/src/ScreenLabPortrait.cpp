//
//  ScreenLabPortrait.cpp
//  ScreenLabRenderer
//
//  Created by James George on 4/16/12.
//

#include "ScreenLabPortrait.h"
#include "ofxXmlSettings.h"

ScreenLabPortrait::ScreenLabPortrait(){
//	startFrame = 0;
//    endFrame = -1;
    rendererRef = NULL;
    useHighResPlayer = true;
    render = false;
}

void ScreenLabPortrait::setup(PortraitType _type, string mediaFolder, string soundPath){
    type = _type;
	soundPlayer.loadMovie(soundPath);
    soundPlayer.setLoopState(OF_LOOP_NONE);
    cout << "media folder " << mediaFolder << " " << soundPath << endl;
    if(take.loadFromFolder(mediaFolder)){
        videoPlayer.loadMovie(take.lowResVideoPath);
//		rendererRef->setTextureScale(640./1920, 360./1080);
        //videoPlayer.loadMovie(take.hiResVideoPath);
        depthImages.loadSequence(take.depthFolder);
        pairing.loadPairingFile(take.pairingsFile);
        if(!pairing.ready()){
            ofLogError("ScreenLabPortrait -- Pairings not ready!");
        }
        
        renderFolder = mediaFolder + "/renders";
        if(!ofDirectory(renderFolder).exists()){
            ofDirectory(renderFolder).create();
        }
        videoTimes = pairing.getStartAndEndTimes(videoPlayer, depthImages);
        
        take.populateRenderSettings();
//        if(take.getRenderSettings().size() == 0){
//            startFrame = 0;
//            endFrame = videoPlayer.getTotalNumFrames();
//            ofLogError("ScreenLabPortrait -- No Render Settings!");
//        }
//        else{
//            startFrame = take.getRenderSettings()[0].startFrame;
//            endFrame   = take.getRenderSettings()[0].endFrame;
//            cout << "found start and end frame " << startFrame << " " << endFrame << endl;
//        }
    }
    else{
        ofLogError("ScreenLabPortrait -- Couldn't load media folder " + mediaFolder);
    }
    filler.enable = true;
    filler.setIterations(3);
    filler.setKernelSize(3);

}

void ScreenLabPortrait::resetAndPlay(){
    lastTime = 0;
    
    soundPlayer.setVolume(1300);
    soundPlayer.setPosition(0);
    soundPlayer.play();
	soundPlayer.setLoopState(OF_LOOP_NONE);
    
    rendererRef->setup(take.calibrationDirectory);

    cout << "sound player duration " << soundPlayer.getDuration() << endl;
    if(useHighResPlayer){
        if(!hiResPlayer.isLoaded()){
            hiResPlayer.loadMovie(take.hiResVideoPath);
        }
        hiResPlayer.setSpeed(.5);
        //videoPlayer.setFrame(startFrame);
        hiResPlayer.setPosition(videoTimes.min / videoPlayer.getDuration() );
        hiResPlayer.setVolume(0);
        hiResPlayer.play();
        hiResPlayer.setLoopState(OF_LOOP_NORMAL);
        rendererRef->setRGBTexture(hiResPlayer);
    }
    else {
        videoPlayer.setSpeed(.5);
        //videoPlayer.setFrame(startFrame);
        videoPlayer.setPosition(videoTimes.min / videoPlayer.getDuration() );
        videoPlayer.setVolume(0);
        videoPlayer.play();
        videoPlayer.setLoopState(OF_LOOP_NORMAL);
        rendererRef->setRGBTexture(videoPlayer);
    }
    
	rendererRef->setDepthImage(depthImages.getPixels());
    rendererRef->farClip = 1200;
    if(name == "jenny"){
        rendererRef->farClip = 925;
    }
    else if(name == "lisa"){
    	rendererRef->farClip = 1050;
    }
    
    if(name == "kev"){
        rendererRef->xmult = 0.0104762;
        rendererRef->ymult = 0.0274286;
    }
    else{
		rendererRef->xmult = 0;
        rendererRef->ymult = 0.0436667;
    }
    rendererRef->setSimplification(2);
	ofAddListener(ofEvents().update, this, &ScreenLabPortrait::update);
}

void ScreenLabPortrait::startRender(){
    hiResPlayer.setSpeed(0);
    render = true;
}

void ScreenLabPortrait::stop(){
	videoPlayer.stop();
    hiResPlayer.stop();
    soundPlayer.stop();
    ofRemoveListener(ofEvents().update, this, &ScreenLabPortrait::update);
}

void ScreenLabPortrait::update(ofEventArgs& args){
    if(!render && (soundPlayer.getPosition() == 1.0 || lastTime > soundPlayer.getPosition()) ){ 
        stop();
    }
    lastTime = soundPlayer.getPosition();
    ofVideoPlayer& player = useHighResPlayer ? hiResPlayer : videoPlayer;
    if(render){
        player.setFrame(player.getCurrentFrame()+1);
    }
    player.update();
    if(player.isFrameNew()){
        if(player.getPosition() >= videoTimes.max / player.getDuration()){
            player.setPosition(videoTimes.min / player.getDuration() );
        }
		else {
            long time = pairing.getDepthFrameForVideoFrame(player.getPosition() * player.getDuration() * 1000);
            depthImages.selectTime( time );
            filler.close(depthImages.getPixels());
            rendererRef->update();
        }        	
    }
}
