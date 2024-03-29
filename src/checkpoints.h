// Copyright (c) 2009-2018 The Bitcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// Copyright (C) 2011-2019 Peercoin Developers
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CHECKPOINTS_H
#define BITCOIN_CHECKPOINTS_H

#include <uint256.h>

#include <map>

class CBlockIndex;
struct CCheckpointData;

/**
 * Block-chain checkpoints are compiled-in sanity checks.
 * They are updated every release or three.
 */
namespace Checkpoints
{

//! Returns last CBlockIndex* that is a checkpoint
CBlockIndex* GetLastCheckpoint(const CCheckpointData& data);
const CBlockIndex *AutoSelectSyncCheckpoint();
bool CheckSync(int nHeight);

} //namespace Checkpoints

#endif // BITCOIN_CHECKPOINTS_H
