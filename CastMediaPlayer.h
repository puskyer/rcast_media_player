/*
 * CastMediaPlayer.h
 *
 *  Created on: Sep 21, 2015
 *      Author: markus
 */

#ifndef CHROMECAST_RCAST_CASTMEDIAPLAYER_H_
#define CHROMECAST_RCAST_CASTMEDIAPLAYER_H_

#include <string>
#include <functional>
#include "CastLink.h"


class ReceiverHandler : public CastMessageHandler
{
public:
    static constexpr auto sNameSpace = "urn:x-cast:com.google.cast.receiver";

    ReceiverHandler();

    std::string nameSpace(){ return sNameSpace; }
    int onCastMessage( CastLink* castLink, const CastMessage& castMessage );

    //Json::Value& latestReceiverStatus() { return mLatestReceiverStatus; };
    uint32_t latestRequestId() { return mLatestRequestId; };
    std::string sessionId() { return mSessionId; };
    std::string transportId() { return mTransportId; };
    void reset();

private:
//    Json::Value mLatestReceiverStatus;
    uint32_t mLatestRequestId;
    std::string mSessionId;
    std::string mTransportId;
};

class MediaHandler : public CastMessageHandler
{
public:

    enum PlayerState
    {
        IDLE,
        BUFFERING,
        PLAYING,
        PAUSED
    };

    static constexpr auto sNameSpace = "urn:x-cast:com.google.cast.media";

    MediaHandler();

    std::string nameSpace(){ return sNameSpace; }
    int onCastMessage( CastLink* castLink, const CastMessage& castMessage );
    PlayerState playerState(){ return mPlayerState; }
    uint32_t mediaSessionId(){ return mMediaSessionId; }

    void reset();

    void setFinishedCallback(std::function<void()> finishedCallback);

private:
    uint32_t mLatestRequestId;
    uint32_t mMediaSessionId;
    PlayerState mPlayerState;
    std::function<void()> mFinishedCallback;

};




class CastMediaPlayer
{
public:
    CastMediaPlayer(const std::string& host, uint16_t port = 8009);
    ~CastMediaPlayer();

    void playOrPause();
    void stop();
    void next();
    void previous();

    void getStatus();

private:

    void loadPlayList();
    void loadMediaFromPlaylist();
    void verifyMediaConnection();

    uint32_t getNextRequestId();

    extensions::api::cast_channel::CastMessage getMediaCastMessage();
    extensions::api::cast_channel::CastMessage getReceiverCastMessage();

    void receiverLaunch(const std::string& receiverApp);
    void receiverStop();

    void mediaLoad( const std::string& mediaUrl );
    void mediaPlay();
    void mediaPause();

    bool verifyPlaylist();

    std::shared_ptr<CastLink> mCastLink;
    ReceiverHandler mReceiverHandler;
    MediaHandler mMediaHandler;

    std::vector<std::string> mPlayList;
    std::size_t mPlayListIndex;

    std::string mHost;
    uint16_t mPort;

    uint32_t mRequestId;
};


#endif /* CHROMECAST_RCAST_CASTMEDIAPLAYER_H_ */
