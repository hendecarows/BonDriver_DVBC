# BonDriver_DVBC

[BonDriverProxy_Linux][link_bdpl]のBonDriver_DVBに対し、T230C対応とTSMF分離機能を追加したLinux DVBデバイス用のBonDriverです。

BonDriver_DVBCは[BonDriverProxy_Linux][link_bdpl]と[BonDriver_BDA][link_bda]のソースコードを用いて作成しました。

## インストール

ビルド手順を以下に示します。

```console
git clone https://github.com/hendecarows/BonDriver_DVBC.git
cd BonDriver_DVBC
mkdir build
cd build
cmake ..
make
```

BonDriverを配置するディレクトリにBonDriver_DVC.soと設定ファイルBonDriver_DVC.so.confを使用するチューナー分ファイル名を変更してコピーします。
設定ファイルはチューナーや地域のチャンネルに合わせて変更し、本体のファイル名に.confを追加したファイル名にして下さい。

```console
cp src/BonDriver_DVBC.so BonDriver_DVB_S.so
cp src/BonDriver_DVBC.so BonDriver_DVB_T.so
cp src/BonDriver_DVBC.so BonDriver_DVB_C.so

cp ../BonDriver_DVBC.so.conf BonDriver_DVB_S.so.conf
cp ../BonDriver_DVBC.so.conf BonDriver_DVB_T.so.conf
cp ../BonDriver_DVBC.so.conf BonDriver_DVB_C.so.conf

vi BonDriver_DVB_S.so.conf
#ADAPTER_NO=0

vi BonDriver_DVB_T.so.conf
#ADAPTER_NO=1

vi BonDriver_DVB_C.so.conf
#ADAPTER_NO=2

sudo cp *.so *.so.conf /usr/local/lib/edcb
```

## ライセンス

各々のライセンスに従うものとします。

* [BonDriverProxy_Linux][link_bdpl]
* [BonDriver_BDA][link_bda]

[link_bdpl]: https://github.com/u-n-k-n-o-w-n/BonDriverProxy_Linux
[link_bda]: https://github.com/radi-sh/BonDriver_BDA
