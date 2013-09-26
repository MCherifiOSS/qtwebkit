/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
 * Copyright (C) 2011 Ericsson AB. All rights reserved.
 * Copyright (C) 2013 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MediaStreamTrack_h
#define MediaStreamTrack_h

#if ENABLE(MEDIA_STREAM)

#include "ActiveDOMObject.h"
#include "EventTarget.h"
#include "MediaStreamSource.h"
#include "ScriptWrappable.h"
#include <wtf/RefCounted.h>
#include <wtf/RefPtr.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

class Dictionary;
class MediaConstraints;
class MediaStreamTrackSourcesCallback;

class MediaStreamTrack : public RefCounted<MediaStreamTrack>, public ScriptWrappable, public ActiveDOMObject, public EventTarget, public MediaStreamSource::Observer {
public:

    static PassRefPtr<MediaStreamTrack> create(ScriptExecutionContext*, const Dictionary&);
    static PassRefPtr<MediaStreamTrack> create(ScriptExecutionContext*, MediaStreamSource*);

    virtual ~MediaStreamTrack();

    const AtomicString& kind() const;
    const String& id() const;
    const String& label() const;

    bool enabled() const;
    void setEnabled(bool);
    
    const AtomicString& readyState() const;

    static void getSources(ScriptExecutionContext*, PassRefPtr<MediaStreamTrackSourcesCallback>, ExceptionCode&);

    MediaStreamSource* source() const { return m_source.get(); }
    void setSource(MediaStreamSource*);

    DEFINE_ATTRIBUTE_EVENT_LISTENER(mute);
    DEFINE_ATTRIBUTE_EVENT_LISTENER(unmute);
    DEFINE_ATTRIBUTE_EVENT_LISTENER(ended);

    bool ended() const;

    // EventTarget
    virtual const AtomicString& interfaceName() const OVERRIDE;
    virtual ScriptExecutionContext* scriptExecutionContext() const OVERRIDE;

    // ActiveDOMObject
    virtual void stop() OVERRIDE;

    using RefCounted<MediaStreamTrack>::ref;
    using RefCounted<MediaStreamTrack>::deref;

private:
    MediaStreamTrack(ScriptExecutionContext*, MediaStreamSource*, const Dictionary*);

    void trackDidEnd();

    // EventTarget
    virtual EventTargetData* eventTargetData() OVERRIDE;
    virtual EventTargetData* ensureEventTargetData() OVERRIDE;
    virtual void refEventTarget() OVERRIDE { ref(); }
    virtual void derefEventTarget() OVERRIDE { deref(); }
    EventTargetData m_eventTargetData;

    // MediaStreamSourceObserver
    virtual void sourceChangedState() OVERRIDE;

    RefPtr<MediaStreamSource> m_source;
    RefPtr<MediaConstraints> m_constraints;
    MediaStreamSource::ReadyState m_readyState;
    mutable String m_id;

    bool m_stopped;
    bool m_enabled;
    bool m_muted;
};

typedef Vector<RefPtr<MediaStreamTrack> > MediaStreamTrackVector;

} // namespace WebCore

#endif // ENABLE(MEDIA_STREAM)

#endif // MediaStreamTrack_h
