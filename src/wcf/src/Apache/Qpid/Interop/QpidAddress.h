/*
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.  The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.
*/

#pragma once

#include "MessageWaiter.h"

namespace Apache {
namespace Qpid {
namespace Interop {

using namespace System;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;

using namespace qpid::client;
using namespace std;


public ref class QpidAddress
{
private:
    QpidAddress(String^ address, bool isInput);

    // the original Qpid messaging address string, with WCF uri sematics removed, and URL decoded
    String^ address;

    String^ nodeName;
    // "qpid.subject"
    String^ subject;
    // 0-10 routing key (Output channels only)
    String^ routingKey;

    String^ linkName;
    String^ deleteName;
    String^ bindKey;

    // node type: queue/topic
    bool isQueue;

    // direction
    bool isInputChannel;

    bool creating;
    bool deleting;
    bool browsing;

    bool PolicyApplies(String^ mode);

internal:
    static QpidAddress^ CreateAddress(String ^s, bool isInput);
    void ResolveLink(AmqpSession^ amqpSession);
    void CleanupLink(AmqpSession^ amqpSession);

    property String^ LinkName {
	String^ get () { return linkName; }
    }

    property String^ Subject {
	String^ get () { return subject; }
    }

    property String^ RoutingKey {
	String^ get () { return routingKey; }
    }

    property bool Browsing {
	bool get () { return browsing; }
    }

};

}}} // namespace Apache::Qpid::Interop
