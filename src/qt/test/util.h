#ifndef BITCOIN_QT_TEST_UTIL_H
#define BITCOIN_QT_TEST_UTIL_H
// Copyright (C) 2011-2019 Peercoin Developers
// Copyright (C) 2014-2019 The Dash Core Developers

/**
 * Press "Ok" button in message box dialog.
 *
 * @param text - Optionally store dialog text.
 * @param msec - Number of miliseconds to pause before triggering the callback.
 */
void ConfirmMessage(QString* text = nullptr, int msec = 0);

#endif // BITCOIN_QT_TEST_UTIL_H
