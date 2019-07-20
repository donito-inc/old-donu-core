// Copyright (c) 2009-2018 The Bitcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/test/uritests.h>

#include <qt/guiutil.h>
#include <qt/walletmodel.h>

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("donu:NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY?req-dontexist="));
    QVERIFY(!GUIUtil::parseDONUURI(uri, &rv));

    uri.setUrl(QString("donu:NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY?dontexist="));
    QVERIFY(GUIUtil::parseDONUURI(uri, &rv));
    QVERIFY(rv.address == QString("NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("donu:NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseDONUURI(uri, &rv));
    QVERIFY(rv.address == QString("NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("donu:NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY?amount=0.001"));
    QVERIFY(GUIUtil::parseDONUURI(uri, &rv));
    QVERIFY(rv.address == QString("NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("donu:NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY?amount=1.001"));
    QVERIFY(GUIUtil::parseDONUURI(uri, &rv));
    QVERIFY(rv.address == QString("NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("donu:NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY?amount=100&label=Wikipedia Example"));
    QVERIFY(GUIUtil::parseDONUURI(uri, &rv));
    QVERIFY(rv.address == QString("NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("donu:NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseDONUURI(uri, &rv));
    QVERIFY(rv.address == QString("NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseDONUURI("donu:NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY?message=Wikipedia Example Address", &rv));
    QVERIFY(rv.address == QString("NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("donu:NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY?req-message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseDONUURI(uri, &rv));

    uri.setUrl(QString("donu:NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseDONUURI(uri, &rv));

    uri.setUrl(QString("donu:NNwUD95yCqxYpWWL2fZqfRTNQreqTffRCY?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseDONUURI(uri, &rv));
}
