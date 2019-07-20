// Copyright (c) 2011-2014 The Bitcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_BITCOINADDRESSVALIDATOR_H
#define BITCOIN_QT_BITCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class DONUAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DONUAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** DONU address widget validator, checks for a valid donu address.
 */
class DONUAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DONUAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // BITCOIN_QT_BITCOINADDRESSVALIDATOR_H
