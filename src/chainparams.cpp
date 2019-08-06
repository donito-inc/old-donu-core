// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core Developers
// Copyright (C) 2014-2019 The Dash Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <arith_uint256.h>

#include <assert.h>
#include <boost/assign/list_of.hpp>
#include <utilstrencodings.h>
#include <util.h>
#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "DONU and Donito prepare to disrupt the crowdfunding sector";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";

        consensus.nFirstPoSBlock = 86401; // About 2 months from genesis
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 86401;
        consensus.nBudgetPaymentsCycleBlocks = 43200;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockCycle = 43200;
        consensus.nSuperblockStartBlock = consensus.nSuperblockCycle;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.powLimit = uint256S("0000ffff00000000000000000000000000000000000000000000000000000000");
        consensus.posLimit = uint256S("00007ffff0000000000000000000000000000000000000000000000000000000");
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nTargetTimespan = 60;
        consensus.nTargetSpacing = 60;
        consensus.nTargetSpacingWorkMax = 2 * consensus.nTargetSpacing;
        consensus.nStakeMinAge = 60 * 60 * 24 * 30;
        consensus.nStakeMaxAge = 60 * 60 * 24 * 60;
        consensus.nStakeMinSize = 500;
        consensus.nModifierInterval = 60;
        consensus.nCoinbaseMaturity = 30;
        consensus.nTransactionMaturity = 30;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1080;
        consensus.nMinerConfirmationWindow = 1440;

	// Hard fork to correct GetMasternodePayment
	consensus.nGMPForkHeight = 47949;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0000000000000000000000000000000000000000000000000000000000250025");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("ef5cd80331c5c118cb7cc4daf1d13462b8c5cf630be5c9586beeef6509a507f2");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xd3;
        pchMessageStart[1] = 0x1a;
        pchMessageStart[2] = 0x3d;
        pchMessageStart[3] = 0xe4;
        nDefaultPort = 26380;
        nPruneAfterHeight = 100000;
        nMaxReorganizationDepth = 100;

        genesis = CreateGenesisBlock(1559882564, 219081, 0x1f00ffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x5f7f26e24291f5be2351e1dcdab18bf94cee718940e6b9f2fbb46227434c3f12"));
        assert(genesis.hashMerkleRoot == uint256S("0x0065657a26307cb6f0ae624c042aeaef21386dfa0c6d4437e2a9996ace2f5375"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,53);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,177);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};
        bech32_hrp = "dn";

        vSeeds.clear();
        vSeeds.emplace_back("144.217.87.242");
        vSeeds.emplace_back("144.217.6.193");
        vSeeds.emplace_back("158.69.62.105");
        vSeeds.emplace_back("144.217.87.205");
        vSeeds.emplace_back("144.217.87.226");
        vSeeds.emplace_back("144.217.87.202");
        vSeeds.emplace_back("nodes.donu.io");

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        nEmissionsAmount = 0.2 * COIN;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        nCollateralLevels = {};
        nMasternodeCollateral = 5000 * COIN;
        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60;
        strSporkPubKey = "0450A906D1033FCFC53F2E622BBDA278271D6BF932FAFC36C7BDBD866C6396416283F5D348C3BCB2E6BB8EC80645678226C7B666C4F37BAFE3BA25EE1525AA5333";
        strPlatformAddress = "NNtPL7s41iNGjysrCFNtGszKTLVruUisby";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("0x5f7f26e24291f5be2351e1dcdab18bf94cee718940e6b9f2fbb46227434c3f12"))
            (  3, uint256S("0xcd8510ef78d9ee45c70b73fe9ed50cc4c5d9989991f42010533d9ccbb88a75a9"))
            (  5, uint256S("0x4084bbb04f01439905553022116c26f2195ee8e9c3df0360ecbfe37909573333"))
        };

        chainTxData = ChainTxData{
            1562885753, // * UNIX timestamp of last known number of transactions
            6,    // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.1         // * estimated number of transactions per second after that timestamp
        };

        /* disable fallback fee on mainnet */
        m_fallback_fee_enabled = true;
    }
};

/*
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";

        consensus.nFirstPoSBlock = 86401; // About 2 months from genesis
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 86401;
        consensus.nBudgetPaymentsCycleBlocks = 43200;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockCycle = 43200;
        consensus.nSuperblockStartBlock = consensus.nSuperblockCycle;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.powLimit = uint256S("0000ffff00000000000000000000000000000000000000000000000000000000");
        consensus.posLimit = uint256S("00007ffff0000000000000000000000000000000000000000000000000000000");
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nTargetTimespan = 1;
        consensus.nTargetSpacing = 1;
        consensus.nTargetSpacingWorkMax = 2 * consensus.nTargetSpacing;
        consensus.nStakeMinAge = 60 * 24 * 30;
        consensus.nStakeMaxAge = 60 * 24 * 60;
        consensus.nStakeMinSize = 500;
        consensus.nModifierInterval = 60;
        consensus.nCoinbaseMaturity = 30;
        consensus.nTransactionMaturity = 30;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1080;
        consensus.nMinerConfirmationWindow = 1440;

	// Hard fork to correct GetMasternodePayment
	consensus.nGMPForkHeight = 47949;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xd2;
        pchMessageStart[1] = 0x1b;
        pchMessageStart[2] = 0x3e;
        pchMessageStart[3] = 0xe5;
        nDefaultPort = 36380;
        nPruneAfterHeight = 100000;
        nMaxReorganizationDepth = 100;

        genesis = CreateGenesisBlock(1565053774, 30320, 0x1f00ffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xb0974c8a9efbcb0359bd08c14155f17ae1fce5b1b23671858e62e19a79d48ca3"));
        assert(genesis.hashMerkleRoot == uint256S("0x0065657a26307cb6f0ae624c042aeaef21386dfa0c6d4437e2a9996ace2f5375"));


     std::cout << std::string("Begin calculating Mainnet Genesis Block:\n");
     if (true && (genesis.GetHash() != consensus.hashGenesisBlock)) {
         LogPrintf("Calculating Mainnet Genesis Block:\n");
         arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
         uint256 hash;
         genesis.nNonce = 0;
         // This will figure out a valid hash and Nonce if you're
         // creating a different genesis block:
         // uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
         // hashTarget.SetCompact(genesis.nBits, &fNegative, &fOverflow).getuint256();
         // while (genesis.GetHash() > hashTarget)
         while (UintToArith256(genesis.GetPoWHash()) > hashTarget)
         {
             ++genesis.nNonce;
             if (genesis.nNonce == 0)
             {
                 LogPrintf("NONCE WRAPPED, incrementing time");
                 std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                 ++genesis.nTime;
             }
             if (genesis.nNonce % 10000 == 0)
             {
                 LogPrintf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
             }
         }
         std::cout << "Mainnet ---\n";
         std::cout << "  nonce: " << genesis.nNonce <<  "\n";
         std::cout << "   time: " << genesis.nTime << "\n";
         std::cout << "   hash: " << genesis.GetHash().ToString().c_str() << "\n";
         std::cout << "   merklehash: "  << genesis.hashMerkleRoot.ToString().c_str() << "\n";
     }
     std::cout << std::string("Finished calculating Mainnet Genesis Block:\n");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,54);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,6);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,178);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};
        bech32_hrp = "tdn";

        vSeeds.clear();
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        nEmissionsAmount = 0.2 * COIN;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        nCollateralLevels = {};
        nMasternodeCollateral = 5000 * COIN;
        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60;
        strSporkPubKey = "0450A906D1033FCFC53F2E622BBDA278271D6BF932FAFC36C7BDBD866C6396416283F5D348C3BCB2E6BB8EC80645678226C7B666C4F37BAFE3BA25EE1525AA5333";
        strPlatformAddress = "NNtPL7s41iNGjysrCFNtGszKTLVruUisby";

        checkpointData = (CCheckpointData) {
        };

        chainTxData = ChainTxData{
            1562885753, // * UNIX timestamp of last known number of transactions
            6,    // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.1         // * estimated number of transactions per second after that timestamp
        };

        /* disable fallback fee on mainnet */
        m_fallback_fee_enabled = true;
    }
};

/*
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
