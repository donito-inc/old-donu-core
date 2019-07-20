Donu version 0.18.0 is now available. This is a mandatory upgrade which should happen before block 47949.

### Changes and corrections

**GetMasternodePayment** has been updated to return 0.4 DONU as the masternode reward.  It previously was dividing the total block
reward in half without consideration for the platform emissions of 0.2 DONU.

**The math for expectedReward** has been corrected.  Earlier revisions during staging factored in the platform emissions outside
of the scope of GetBlockSubsidy and has since been changed.

**Some branding corrections** have been made addressing references to "bitcoin" and updated to to "donu" and "DONU".

**Mining payouts** have been corrected to include masternodes during the proof-of-work phase.

The default port shown in the **masternode.conf** example has been updated to reflect the correct mainnet port.

**Image updates** were made in src/qt/res/icons as well as src/qt/res/movies as well as **copyright** information

### Installing your Donu wallet

We would recommend reading the following articles if you're unsure of how to use the release files or install the new Donu wallet:

[Linux Installation](https://www.donu.support/portal/kb/articles/installing-your-donu-wallet-in-linux)
[Windows Installation](https://www.donu.support/portal/kb/articles/installing-your-donu-wallet-in-windows)
[MacOS Installation](https://www.donu.support/portal/kb/articles/installing-your-donu-wallet-in-macos)

### Support & Communication

We have a support portal and knowledgebase available at the [Donu knowledgebase & support portal](https://www.donu.support) and you can communicate with the team and the community at any of the locations below:

[Telegram](https://www.donu.io/telegram)
[Discord](https://www.donu.io/discord)
[Matrix Chat](https://www.donu.io/matrix)
[Twitter](https://www.donu.io/twitter)
[Facebook](https://www.donu.io/facebook)
[Reddit](https://www.donu.io/reddit)

