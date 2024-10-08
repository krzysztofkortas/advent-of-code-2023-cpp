#include <string_view>

namespace day25
{

using namespace std::literals;

inline constexpr auto sample =
	R"(jqt: rhn xhk nvd
rsh: frs pzl lsr
xhk: hfx
cmg: qnr nvd lhk bvb
rhn: xhk bvb hfx
bvb: xhk hfx
pzl: lsr hfx nvd
qnr: nvd
ntq: jqt hfx bvb xhk
nvd: lhk
lsr: lhk
rzs: qnr cmg lsr rsh
frs: qnr lhk lsr)"sv;

inline constexpr auto input =
	R"(xhb: xng xdp ntl nlv
gfz: fml
tht: mjk dgk lsc snb
xqk: jlb
grs: hcc
gks: hzx kpc hzg
cfj: gbx mkj rrx
dhs: fxn rxj
dvv: tmb pnj dqf lsc
qdn: gds pvq
dqs: bqc
tnk: lkv
dgc: qlt lvc gmj llm tgm
nsn: dcr kcn fpl sdq
ntk: nlv std rtx nst tlg
zhl: vsd sjj vtl bbp
gqk: brq
zpt: pqm zdp hkh znv
gdq: gpc cmb
lpl: jpx
ksg: qjv zgb kbv
hcc: fxv
zdf: mlx zjm fks jxg
cnc: qtb ggf
xtk: psd bln pcj gtc
fbl: qzb
svk: srp smq hcc
mdm: fxn fkb bpb bkk
vhq: rbl ktz pvg
xbm: zhp jbj ffd
dnv: sbm hjp
hvt: rhb gtv ksp nsr mcv
lkp: lgq glp
lsh: cfg
mmx: xpg jfx pzb scf
qfp: hcf frb mck
llk: sfc
bqx: nvl txt pbl xqb
zhp: rfg hrs dhn
kmc: zjt njh xdl
fcb: vvk dmk xmp pzf
tcd: vvb
bpb: sht dfc
hxz: jgt dvc mdl
jks: qlg drj tlq rfg
rtx: mgt pxx zbh
qlv: mgh psq nzf lsh xpd
vxq: shv jlq hrd vrg
bpm: kpf rpg mlz
hzz: tzc qbn lpc
pzf: rpr
kzl: xkm
lpp: pjp ckj rvv zfj qxz
dzn: crj jzn
ckf: ljt vpm sfc
kln: fqf nvd qsk xrp
sdb: ffs nbp gkg
xrp: kzl
slk: gbx
znf: sjj mzg
hfx: vlk
bpr: zpz ctn bmt
pnm: kpn zhp mgt
hfm: vzz rrx
zlp: hxp nkq flj
ctj: llk ldc zgm
bfc: xdb
hsj: bzt krl gls dpv
njl: bvn dqg hdf
gvj: nqm
grt: tzc
fnm: cjz kkz qcl
ppc: khj fxg
fnf: rck qnn qnp
xxk: jrt
hgr: krj
zkf: nst
nzb: kxq tzc kjt
qqv: zsk dpb zkf nsr
llm: sht
dcd: kvv qsk
rct: bbt qqr
pgk: rrm vrk pdx
gls: kpl
shq: pdq vtl mhq msq
fqk: fgv crb fbb
xhc: bpj hgr
mzt: dnm hvp fms vxd
tnc: zqz vqf jnj cfm
fsp: ggf cll zqd smc
pvz: ltm
glf: vgh bht
mzj: bnf hlx sdq vrg
ktf: mgt hrj njh dzg
dzl: sgz rxj
nfm: tzf
lfl: srf lff frt fjg vqp
sjm: qkm zpg
hcx: pcj ghn qmz bxj
jvr: zqd xkf gpc
pkv: qqm gds jtk
xnn: ddx qkl nnn gqd zkf
jlq: xpd
gqc: jrv vrn lpt frp rzk fmx
qln: frb dfc lmx
fdl: rrq rmr mcc dmt
tdg: kvq skr bvg
kmx: vvk
xbp: bdh tnq qrt
cdz: qgl ghp npz lvm
sfs: bxv cvj hdd mdg rxj
fnn: qgs
vvb: tlm
xmm: dkm
bht: cbm rvv
ksp: hjc
kpn: jxr mpk
vzt: vth xvg vcl lfn
jkn: gnp gpn jbk
bmf: jzk dcl tbv jtp
fqc: pjl vjb xss
svq: xmp
qqj: snb tmq nrg
dqf: qtv rxq
bzd: dnc hrb npl
rks: jjz
scs: src
qmm: nmz xcz vcz rrq
rvc: cch hhj sgv mkv crp
gsl: hgv rjb gnt gpm
bzr: vsd vss dnv
svp: zjf jhj
gzl: hxd vxk
gkb: zvh hmf
bqz: kcn jdn
jtp: jbm vsq kqg
kbq: qgl kvt
kzc: nst zhn qrs
nnp: nxk mpv bcl
nnz: chq
kkb: pgv qjv nqm
rht: mqr bxv jzn
lqq: dgk mdl nmz
cql: mmb
ccr: pvz jjz nzb nqm
nbg: nnx pzb pxx jrt
hvl: hfm kzl
fft: ktj
ktn: vlk vsq
dcx: zgb
hfd: nrs cdr pnj ctn
qjc: znc ffs nfc ncz
bpx: nfm rhs fxn
fkd: qfj pmp xdp stg
lzt: fqc pqk nlh xnn
gtb: phs pxx cng hzx
qdk: pjm
zlq: zgz llb slk hdf czx
xvg: lzv
dsl: hzk vjb rks
xpr: dcq glv zmf
mlz: mnd lpc rjq jvc
ggk: pfc rlb rqx tdg zks
sbr: rbl kzs vln qlg
pmn: rxq ccf fzz
xvp: nxb rmj scs
kpf: kcn hhd tnk vzx
zjx: rsq qhr ngj jmr
lsz: kkp
lcq: zkv jbh vsx hgd scf qtq
drv: qlk
rqx: ggz
cjz: dkl fzv pkj
tnm: ztd bbt
dmt: rrx
jfg: kbq bbt
sfr: brh gpc jvb
ghr: cgh nvc
msc: gzt gzl mgm dmk rql
dvc: zsz hhr
llq: zgn xlr mmm
fqx: pjm src vrb hzb qgm
vlq: tlm flh gbx
rtn: xml
chq: rcp vmk
xng: qfc pbz
sfh: dcs
nxk: dkl nqk
frb: hzz zst xbv
tnq: psl
lrn: lqb lqn qml
jgl: hrj mzg dnv kmc qnq
hxd: brq
qlg: jpt
scc: nkq
mds: hts qkg dvc
mcc: kss kmd zpz pgs
qmr: kzx mrd bfc
rjh: vpm jtk vln
lhg: bxx pvz csm
tpm: vrg ddv smv pjn
dgh: qfc kkg xvp ssv hzd
jvn: dmk lfz jxs jfg bsn
dcf: tsm jhh xss zkf
kmn: gpm qqv bzr bnf
ntl: xnb ggz ddx
qgj: zth gkq
vpk: sns dpn jtr
mfm: tvg psq sjj
sss: gzg pkk qlp
kkp: tgl
vrv: nlm
dsj: smn pfc jvc bkq
ftf: pgv hqf vjb
xfr: mmm stg zqm dhn
bkk: vtv hsd
sdd: tnm rcf tss sxv
ltl: lck cpb jcc
sbd: xgt fft
fjg: tfz rsg kmx
cgz: jrt ptl phf hzz
ppk: btd prr
dln: rpk nnp ntf glf
jhh: vss hsd qpl
cnh: dpb rjl djv
xml: fzf
sxh: fzq drq sfq llk
jqc: dcx
cxp: dgc rtn grt rdl
lsq: pmk hzg dbf
fzt: qnq ffd qrp lnt
jzd: zhz dfc
ghp: plb zxz lxg
csf: qbm llm
tlh: nnf dmq zlg mfm
qgz: ptx pxx xqb fpl
hbg: ktn rvr vvr vrk
gld: ghn cvl jzd
mqs: qzb bmt dgk lpl
psq: pql
jkz: tgl rqg sbg kjt
rbl: kvt
znk: qgk hxd jkk xzc
jhd: bpm hcx zgn nsk
npp: btd btz drv nmg glk
bpf: sdb ldb hfc
ngj: rqx
dpv: qtr mht cvj
qqd: zck
fhs: nxk khj jpx
mbk: rcm smp ldc vcl
bxx: scs
qdl: plb fzz hjf prr
rzr: mcx smn nsx
lmb: gmv zgb pqk rkt
skm: lvm qns vsc dcd
spt: psb srp bkq
dfl: blc pbz ffg hnn
hrd: nsr qgs
csm: vxg nsx
rbh: std
vzc: jbk
xqd: sjj
jpt: rcf
qrx: krl njk bmp
rjq: tmf xss vbn
jfx: pjm zdj dzl xpb
mlx: rrz lrn qqk
hpp: jrv smn mcb jlq
glv: dll xlc
prv: vqb qsk szr
fgv: pbh gtv
gmj: zdj qdk csg
bms: dzf fkc vkq
rts: bzv pfl qnn
hqh: ltm drx
vds: mqm vnb jqr pdq qpq
vrq: vxg pnm klg bkq
ndt: hnm dkn mvq
lrx: hhd
fnx: xmm vrv vcz ccf fht mhd chx
nxb: qrt ngb rbc
pgh: bdh
dsg: bqq dhs qmz qfj
vmz: fzv xmp gpn
jgc: nmr xxk pgv pvl
mxm: gmj sdq
kbv: lck
sxv: bsd tsf
jqm: ljt bcl bfx chq
xmc: gph dsr jvr
ngb: dcx
mcb: tnq
lrr: chx svq qsx nqk
lsg: zjm qkm xbv
hcf: vtv lnt
cmb: rcp ccf
fzz: vsq mzl hfx
tbj: cqq lzv
nvl: hnn
jht: llp hxn
tqh: dxd gkl
zfv: pjn bvp
bvq: bmp zmc
ssq: rhs mdx gnx dbn qgs
vsx: qtc qpn vjb
bjf: gkb jfg mtb npp pgs
lvz: tlg tdb bvg fml fqk zks qjv
zbh: jqr gjz
fhn: pmp ltm
jld: grs mpk
jcg: sns pfc
xpf: hhr hxp xdb qnp
rvr: zjf thc
jls: vrf zhz rxj lzp vpk
pbz: ldn qml
nrr: lsc vth zgk
rzn: vmk hxl lzv
sgz: srp
hls: ktn sfc jcn prt
nsq: crj tgm jvc
sjv: mnd qxl lvc
ntf: sfq
gsk: ggq jtr zkv qdk
smp: cbm
ntp: kbq ggf
vhb: kvv
dlp: hqh kpl kjv cgz
tdp: xqk fhn rks xng vrn lrq qbh
smc: rcp fjf
fqp: tnn jdn gls zcb
fcd: krj sfr mdl xhc
mxc: cll
tdb: zhl qhx dzn gld
mmv: brq vvb zgk snr
zhn: gbz
mcv: htn mgt
qnt: hts spx
cng: gfz tnq
zqt: mqm
kvq: jjz crv
crk: fzf
dzf: xlc jpx
qhd: rvr mzl bjv rgp
pns: jtr xpg xtx vfj
jqr: qrz
jzn: vnb
zqd: kbc
bcr: zzp mtj gqd mrc zst
jmn: vhb hlc phg vzc
mdl: llp
jpq: bdh qlt hht pxx
qkm: jrv
qtr: ffn
flq: kvl qrx rzk cxj
hnd: tkv
rsd: csr tvg hvx mck
mvk: hts cdr plb sbd jmv dqm cmr
dpp: qrz bxj
bsk: dkl kxg svp nbp
fnt: hzg
flj: tlf hmf
pfl: zcz smc
rkx: bbp dss fxq fll
ctn: vln tbj
hbs: jlq zdj
hrj: nnn
lvj: smp pzf rcs
vtl: shn ngb fmx
vtb: gmr zpg ztc
lkd: ldl vlk nfj rpr mxz
sfq: hgz
zgr: btd krj pdx
zvh: mrd brq xcz
qtq: zds ngb
zqp: csr
kcz: lzv mvd
mtb: zsz
sns: kxq
bvn: fft vhq qzr gdq nqx
xzc: lth svp ztd
flr: jrt cfv scs srm
qtt: jrs gmr jlb ckq mfc
bbs: plx fzf nnn knm mnd
bcl: fkc xdt
xdl: dbn
jfs: lfn jxs zfj lcg
rkl: hbs bxx cvl nvl
jhl: bxj bgm lck spl zlt
gjz: jqc dqs
fxv: tgl
bnf: fnt zzp
pcb: nsj kvv
cbm: btd
glp: jzk lrs vqh
hdm: kft
gmv: pcj gqd dbn
vnn: zhz bvp fxq
vhv: gpc vvr
ctl: rrk mgt frj jxg
rhx: stk dpm rbc cgh
szf: hxl vnc
gtc: zqt nsr vft rgv
ksz: hfb hnd
bgm: pmp psl fhp
nth: kmx rrq xvv
dnl: tzh fbl qjl
zfj: nzh qkt lqz
lrp: vkq
dbf: pzd zks
gkj: hxp gkb
hzg: csr
pzn: spt lrm hrh ztc
lhf: gdq czx plj
rkr: lnh
pjf: nkq gbx bpc dnl tbv
srf: hsr nqk
pvg: llk
qcb: dmf sgt lrp
qxf: qsd vpq slk jnp
cdk: gpm qhr qgm
pvr: kxg ncz
qjm: cql mjk mds
vgr: gfz smv nnn jxg
hzx: kcf
htn: smq
qhr: fml
sfg: kxz tvg tvz
tfz: dmk npz nvn
sbm: pjn
zhr: vqn kvc fzj qmz
qzp: kbc
mmp: nsk pxf zhz kpn
psd: mxm xpd frj
zjf: zmf
dsr: qkg rlk nvn
gcz: jlq dpv zqz
mvr: vrk dgq ppc vsq
thf: ddf tnr qgj ncv pzv
btz: sdp qzp czx zlh
dmg: fhs fkc mxz jvr
ptx: fmx
rbc: sbm
bzt: ndk jcc kcf
ztq: kkt cll qgk
rhb: vtb jtr htd
vsd: zcb htv
xdp: ffn
ddv: fpl pjn knm
hfc: gbn hxd
hhh: mqr mrc
ffg: frj kkg
fhp: lrq znx jmr hqh
llr: vdz qqd qrs csr pnd fks
cvb: rfh phq hxl tsf
khc: dpm rkl kkg zfv ktr rrz lzp
qkl: kvl bxj
bzl: lnt rkx zgx
zpz: npl
mdp: lth nrv vms dxx
vdb: jcn pvg ksz fxg
lqn: zhz jld
cpc: zbx vzz vlm dcq
hgv: qkm jqc sjv
kdf: tbd slk qqr qzr
fzq: kdb xdb
fqf: ktj mrd
mvq: mbz zhn
qvr: jdn tvz cvj bml
dqg: dcl rxq zcz
vzx: pgv vfj
ndz: ltr vsn dcs gjr
qrz: bmp
hjf: lss pkk
ntx: klp vcb qfp pld crp
xlr: fzj
czx: qlp lxg rcs
vpf: rsq zhz
ndk: vnb
fkc: tsf
vgk: hlc fvx fnf vcl
jxg: pvl
nvx: rck hdm lxp
vtk: qxl rsq srm hjp qgm
hzl: mtg tpk zrn bxj rrz
jjc: ktn lzh gzg gqk gkr
htd: lvc qmz zqp
ddf: rpb
vvh: sjm nvl krl bqz
sqh: gkl gmr
qhx: shn nqm zcb
fvj: dmt sfq xjm jzk znv
krb: jkk hrb hgp
vrg: lnh
klk: scc bfx
cjr: vvn jnp jht
vsn: lzh szf sxv sgt ntp
dsx: tdj ppc cql fdt
frj: dzg
gkq: kzx
fnz: nlm
mdg: sqh dqs hht
hrh: rrk lzp zqt dpn
sgt: glk
tmc: nlm hvb
psc: vnm lqn csf xbv klg
grr: brh gpn lpl
blh: cxt
rkt: csg hcc
mtg: kpb rmj lbf
lmx: nzb sdq gmr
mck: xpb gcz dbf
pbs: ftv hlx bzl
xnb: bbk cfv smn
fvd: smn nzd qqz gtb
pqk: mqr
bhc: sns vrn
jbh: psl xjb ksp
gvz: hfc ppk lrl dxx
jlh: pcb
qbh: lsq dsl rkr
rsl: stj nsx dtl mcl
lkv: hzb lrx
jck: jbm lvj ncz
vtv: nsr
gph: tkq drb
rrp: ckq mtj stk rgv
dvx: jbk rvv lth rzn dnc
ktr: rht hcf kbv bvp
nmc: mmm jqc sht
vvl: slv pbs xml
vvn: vqb fzq mpv rcs rcm
gfn: pbn dkh mxc
hhr: kkt
ljc: qtc cxj mhq
kvg: xcz jpt hgz kvv
qsf: qgm lkv zst tnc
bsq: krj dfd qgl
xkx: bzr jld vxq xlr
lhx: zgm vhv kft
bkq: hzx
pzv: vzz nvd
bdv: hsd ffd hzf jgf
slh: qnt nsj qjl
mbm: zpg shv kdp fnt
rlb: svk bnm
bks: vcl prv crr xlc
nzd: ksp cqx trf tcn
bdk: jbk fnf
thc: zdx tsf
ffq: drj vqp rrq bht
tsm: kdp klp zgx pzd
smq: fzf drx
qbn: gkl
tdk: tcd qnn nvx xds rcp klk
vqp: bsd tbd ppk
zph: hsr bmt cjr
ltr: lth mgv mds
zck: xbg rrz
gbj: cjz cxt nmg
rmp: ldb lrl cjz rrt
lqb: kzc ndk
pnd: dqs rkr
bnm: tnk hpr
lrq: qms
zdx: fnz tnm kjc
qnn: qlp
dfd: rjg sdd jhj ptq
spx: nrg
gmr: bth
tnn: src trr
ftv: psl jgf
bbd: cgs
ppm: csg bqq dzl gqd
tdh: ctn qth qsd kzl
qcl: zxz
lfc: mrd hgz rcp
qqz: vnb vss qbn lpc
rxq: pbj
pld: bqz lrx
scz: zfn qlg dll tcd
qjx: pvz znx lsg vbq
flh: qgl sfc gsz
sxt: tcd pjp pbg hjf
bxj: tmf
xtg: vxd lgt jkn qgj xxh
vxd: tcd fsc zft zth
qgk: qsx
qmv: hqm
vxk: cmb kqv
crq: bvg
vpq: vnc
bzn: tbx pjf ggd scd xgh
qkf: lgq lkp lqz chq
scd: mtb dfk
xqb: qkl ptx
rgp: mkj qqr xgh
stz: zjt nsx kcn kpl pgh cnq
rpr: qlk
tvb: hlc nmg rrx
pnj: blh
xvv: qcl
bfx: pqm
tjv: vqh lgq vzc pqm
qrk: hgn gpn llk rqf
vlz: mbz xqk gqd phf
qqm: rlk plb
zqm: cfc qmz sjj
tqr: mmx cqx bxx ngj grt
qjl: nnz
nbp: pdx kbq dgq
hsr: qtb zxz
hqm: rcf
rdh: gls jqc xtx qtt
cdf: ffn dzp qxl bln
tgd: hqf rhr lzp qtx
hjp: dtk mbz
gbx: jbn
mzg: tlg fmx
rld: bfp tmb lgt szf
llb: dkg nkq xmm
jrs: vcb kxz kmc jbh
dcq: vpq
rzp: gvj lsh fxq
rhs: qkm
ccb: dcr vvl kcf kkn
kzs: nhg vzc tlf
crz: gnx
xzp: vxk cgs hlv
zcp: zjm snb gbn kmd bfc
hnc: mbk kkt lcg dkm
fpl: zlg
bnx: gsz vnc hfm pkj
ljt: pln rlk dgq
vfj: zst
kqv: gbj hgz zkd
fbb: crq fnt bvq
xtj: llm kjt kdp
bml: mtj fnp frp
zft: spx xhc gkq
rjl: cfv hrd
nqm: lsz
xsr: bvq svk khr
vhj: xbm crz bnm rsl
fxg: rrt
btt: gbz zmc dbn mdj
vpm: xlc bpj vhv
nbv: jlb jcg sjj zzb dtl
vcs: vsc lqz
pkn: ffs gkb glp
plx: tpk qlv xdp
vrb: ssv lvc zcb
kpc: pqk dcr
xdt: pkk
lxn: vhb ktj hts
zth: vlk
lss: sfh
gpb: lkv tzf
fhm: gnx ptl cnz gtz
zfn: vvk hdm drq
kjv: mrc nmr smn xkk
tkv: jvb
jdn: tvr
jnk: fzv lpl dvx
vjb: mcx qml zgb
ttf: vgh qzn
hvh: gsz hnd
vjl: cvb brh hts ljt
rqf: ttf xmm mzl
vjn: mhp
msq: qqk csf vqf rjb gqd
nfj: fth vpp gds bsq
vpp: krj fjf
pbr: drq mmb qzb
dml: ffd vqf
mgv: jxs vnc xrp
dxv: msq gkl mlx rqg
chc: lnt pbl qhr vss dpn
vlm: tcg qjm kjc
nrs: qnt pbj pvr ljt qkt qzp
rrn: pfl dmg ctm dcd nxk lmh
jcc: hpr mrc
mdb: bhz tnr ppk
tbx: sdb bsd tgj gbn
ffk: tkq lkp jvn nxk
xkf: rcp
hgn: mdb jjc rrm ldb rjg
gxx: nsj bzv mzt dcl gfn
qpl: dcr
nqj: cbm ppc qkg
kjm: zhm lth npx
zrn: gtb shn rbc hzb
msz: qxq dzp ftc rzp cdd
vqn: mpk kxq tzc
cch: mtj dfc
xcn: pxm qbm dlp gks
zbm: ldc tgj ngg nsj
gtv: mbz fxq
rmj: fxv
pgp: pbg dqf hgr dcq
qnp: rrq
kkg: crv
npl: ktj fth
mqm: vbq
jgt: zsz rfh nmg
stj: qml ngt vxg
lpt: xpd kcf
gnp: lss
dcv: fzj jvc ckq
snl: ggf
npg: gls qmz xtx srp
qcn: bpr zcz ctn dxx
hxp: ljt dzf
ngg: xdt
zgz: rpr vvr vhb
xjm: lmh pjp drq
mfc: pmk xtj pzd
rnb: dfk rvv npx rgb
lrm: fll pql zfv
xtc: crv
hnm: stg fnt
sdj: jmr ksp rzk khf
vtj: qtv pmn tht drq
ddx: ksg pmk hbs
hht: hgd qpn cnh
mpv: pln rfh
zmc: dtk
znv: xgt ckl rrm
kdn: gbn zgm pkk lxn
dxd: jxr
jcn: fjf hvl qzb bsd
zgk: snl xqf
fll: rqx tmf
nnx: lsz
qfj: rtn hjc cfv
jsf: bhc cpb drx
mdx: ssv
lqz: hmf cxt
kmd: ldl llp
hdl: hrr xzc hxn blh
nsk: mdx rkr tvz
rbt: cfh kss
crb: qdg mgh gjz zgn
xmp: thr
zhm: dmt hvh kjc bsn fzv phg pvq
cmq: mfl nvj njl rlz
rpg: pxx
jsp: sxk dsj xtx bbn
vmx: xkm ffs xcz vcl vrv
prn: jzd knm khf hhh
kvt: zgm chq vqh
jpg: bbm xml hpr
zpg: kkp
nzh: fqf zmf llp
khf: hhd cng
lfn: blh
prc: grs qxl pbl qqd
kps: dss zqz rmj vtv dml mxv
dlz: ztd pln qlk tbv
zsk: vpf trf
rkz: vms kbc kcz
fkb: ggz mfc mxm
tlr: tnn cfc zqz xpg hpr
zdp: kjm pbg jgt gph
bzv: gpn djs npz
hjq: xmc cmn tmq pqm
dpm: rmj gtz
txt: fnn
skr: bth ldn zst
pqm: vsc vmk
vbn: tvr kpl
nlh: qtq rzk jzn
pvj: hvl sqk glf cfj
mkf: tkq hfd vcs tzz fms nrg prv
vft: gpb kpc vsx
pdq: cgh nmr
bbc: grt cfm rkt bbp drl hrj
lsc: rpb
jfh: klk xpr bhz ckl xds
jcp: bxj gdp ndk bpx
hsd: zzp
pmp: hjc
mcx: cvl
xqp: lrs rpr
qtx: ptl xsr xdp fpl
fbs: frj btt sqt kkp
tlf: rlk bsd
ldc: kmx dnc tlm
xbr: qdn nth pjp gzl
tzz: xgh pzv ngg
ksh: rbt bfx mfl zlh lrl rql rrm dkg
sts: qzb svq xdt chn
hrc: kpc vqf jqc jjz
lmh: sfh bxt zsz
vcb: lnt
vgh: pbn bpj
bpc: fth dgk llk
mhq: kxq dgc
dgq: xkm gzg
vnz: hzf mbm xjb xkk
chn: qgk fqf
hsb: pkn vvb rkz drv rqf
jbj: ghn ffn
zlg: fxv
qrp: xbg hrs qlt
jjf: zqp xjb srx nsq llq
psr: gjf xmp kvg ztq
ckj: glv vsc zcz
xdq: bjv rbl zlp mgm mmb vms
ldn: stg dtl zhn gbz lsz rbh ztc
npz: spx
fsc: fzz tbv znh rck phq
psb: dmq khr htd
vsg: hgz chx lxn gjf vgh
qrs: xlr mbz
gtz: pvl
kqg: xvg xxm xmp
cmh: zgr bzs pvg ndp
kkt: prr
tcg: gzg vmk hvb
vvx: bpb lpt qdz pzb
hdb: pgv shn jgl jcc
ggz: zzp
qbm: fxv
rlz: brd cgs hnd zkc gnp
fdt: ntf bvv
klp: qtc
sjl: jsf bvq bbk qms vbq rks
klg: pld sgz
ptq: rcf dkl
jtr: djv vjn mfm
xxh: drv hrr nqj tgn
tnr: kss
pfc: bdh
nrv: hnd jht
nmr: hrd zks
msv: cdr rlt nzh zjf
mmm: vdz
vpr: vzc nfc srf bpz hjf
trm: frt pzf vcs xvg nnp
bzs: tvb fvx sdh
hdd: fnn bhc tvz
ktz: rcp
qmh: gjf lcg mdl zth
bcc: sqh nmc jcg cpb dtl
jqf: lqn shn kvq xqk
mqr: pbl
glk: jbn lxg lrp
jqs: nhg sgt
ckq: fxn
tmb: ptq nvj znh zbx
jnj: tlg fnn zgn
nlv: bxv
zjt: mcb
rhr: vdz zjt sxk xsb
jmv: jck lrp dmf
rgf: dnl bdk grr bbd qlk rct
lxp: rrx jtp jqs fms ffh znh
qdz: zjm nlv
dcl: lfc scc
qjv: src pxm
hfb: zxz
qqr: snb
hgk: prc fks dpb qhx
xgc: rlt dsr kxg xvv hlv
kkn: dpv pbz ssv
nfc: qns gbx
pcl: rlt
ldh: pjn jxr trr mnd
vln: ndp
zkd: cfh nvn cvr rjg
dmn: znc phq qth cfh tmc
lff: dcs smp
hrr: dxx jht
lvm: tkv
krr: kzl rts hfc sfc
fjt: hdj lqb pld pxf std
hdj: pql bxv shv rjb
gxp: dsr nnz jlh
rrk: zpg rdq
qzn: nmg
jzk: khz bbd
qkt: fnz dqm
mkv: rbh ngt dzn hgd xqd
jtl: mfl qqm krb kbc
hxn: rpr vkq
npx: jvb ndp
sgv: jhd qrz ftf fzf
smv: sxk zck dcv rdq
nvc: qbm dcx
zkc: scd pcl nhg
brd: jnk rcp
ffh: cmb sfq ztd
qpq: crk xbp zqp sht nfm
nqx: gph hfx snb
jzm: zdj dnv ffg fhn
ttg: fvx tbj rpr
qxz: vpm hmf gqk
qsk: rrq rfh
bln: vbn xtc
pcj: qnq qlt xtc
tcn: xjb qjv
tmf: gfz
fbp: nqk phg tzh
tgj: gfn hrb
drd: phs pbz tbf hnn
cfg: smq rzk bqz
jgs: mgh lrx pgh
xpb: dhs vpf
dkh: bfc jvb
rsq: fzj
vqh: hvb
nvd: ndp jkk cbm
sll: sfx vmz lzh zlh
nkb: npz rql qsd dqm
sgk: bdk fzz nmz pgk
csr: scf
fht: qth lrs qqr
dss: scf dtk
bfp: qkg ntp
pvb: dkm ckl kft btz hlc
tzf: tgm
xkk: tgl qhr
qtv: pcl qzn
hzd: mqm drl mcx mhp
ggd: rsg qlg rpb
blc: hzk zhd bth
pxf: vjn jxg
znx: bqc sbm cqx
xxm: rbt ghp
zhb: tfz zqd fvx vpq
hdf: ndp khz
rgb: qqj xrp
lxd: rpr mjk ckf kcz
xsb: hhh kbv
vsq: xqp
cvr: hlc kvt
fcx: mvj mrd slh xzp ttg
bbn: gvj skd htv pmk pjl
xgt: znc
pjt: jlh pbj dmf zjf jht
llf: rmp hfc zft snl lhf
dzp: ffg dpv pnd
bxt: drb ncz drv
rfg: gdp lgm ngt
xlc: qzr
jpr: dml qrx kvl lgm qpn
fks: crz tvr
bcp: bfp lqq dfk kxg
xzz: bcr ksg dxd lnt
kjc: pgs
cbr: ltl bvp vfj sxk bvq
sqt: hcc rgx psq
slv: pbs ggq mmn psb vcb qgs
nnb: xqk qdz jlb
sdh: kss pln
hvx: pqk mht trr
rck: dkm
bth: ptl
zjs: bvg bqc nnb rjl
kdb: hxl jhj
jxs: hqm kzx
tlq: zgk tmq sbd
bbk: drx
tlm: zsz
hqx: bbd gkb
lbf: mpk hzb
dkn: nvc stk qnq pzd
hgp: gjf gkq
vnm: mht tgm qbn dpp
pzb: cpb crz
zsg: fml jqn nnx qln zlg smq
vsv: xqf slk hqx vth
vdz: pnd
gzt: lss ttf hqx
mfl: vcz
hrs: lnh ngt qdg
plj: qmr lhx bcf
fvx: nlm
tss: jpt ktz
vzz: jbn
ztc: htv
kkz: svq vrk tmc
hgd: qgb
cmn: pcl nnz
jbm: hsr kft
rmr: fms jlh xzc
vrf: jpq dmq kpn
dmf: sfh
qfc: klp qqk
drl: ghn
jnp: drb
jqn: gpb njk cvl
nnf: gnx
lfz: thr kzx dkg
rgx: kjt cgh xrv rpg
bjv: dkh dqm
dkg: mkq
lnn: pql qqd ghr fkb
phf: pvl sjm
gpv: jfz ggq cxj qtc
bbt: xgh sdp
spl: dxd ffn
fzv: bpj
xqf: ckl vhb gsz
rsg: nsk qsd tnr ngg
drj: zbx snl
qtc: txt
rcm: djs vpm
bvv: pvr cvr jhj
hjt: kss ldb dvx nxk
dzg: smq gkl
ldl: phq jkk lrl
xbh: rxq lfn ztd brd
tbd: vln qsx rjg cnc
prt: cqq gbn qmv
vxg: vnb
zgx: dpp dzg ptx
cqd: scc qdn fft gkj
ftc: xdl qrt gvj
mxv: bbm lnt crk qkm
cfh: prr
tzg: jqn nnf pgh kkb crq ghr vrn
pbh: bqc fnn
rzk: hzz bbk
xgh: zxz khz
zzb: drl gls xjb crk
cvx: qcb mkh qnp rpk jpx
cgs: vkq
bgk: qpl kdp ggk ltm
hmf: mvd
srx: ltm rjb
fkq: khc sfg qrs crv
zsn: qcl nbp qlp rlt
dvg: dll gsq zfn ctm
gnt: bbp bcr ntk
zvn: spl zhd nsn rlb
gpm: nqm
pbd: hfb jbk chn fjf
tdj: qth hqm ktz
mxz: vqb ddf
frt: pbr znc qsx
tpk: pbh jmr
qsd: gds
tbf: vjn fpl
nqc: vnc jqm ckj tcg
qgb: jgf qtr sns
dmq: kcf
pzl: mbz xqd dcv hpr
qgl: jbk
rsn: tsn fxg bpf bms rbt
cnq: trf cdk fqp
lxv: rdq srx crj mqm
mjk: blh
rxx: mdj xxk nnf ljc crq
bqc: bmp
rdp: vqb vql mvd pjp
srm: stg lpc
ctm: rrx
mdj: rkr lck jgs zds nnx
kbc: rql
xds: ncz nrg
rdl: fbb bqq zqm
kvc: djv mhp
pbn: xgt
zcl: ndz glk jtk cqq
crr: mhd qmv
vvk: rpb gqk
hqf: vzx hhd
gjr: fnz gxp sfx mtb
vql: fjf dnc ddf xkf pbn
hkh: ksz fqf nvn
mmn: ngj mvq bqq
jcq: bth std txt tvr
pdx: mvd
kpb: tbf rdq pjm
kxz: cfc cch csm
ddr: gks xbg qms dpb gdp
mnd: htv
hzf: jgf fgv
cvf: dmt gkj jqs lxg
khr: rhs xdl
mkh: prr cqq hqm
nmm: cxt fdt lgt vsc
fnp: cfc bkk
gkg: gnp rjh jlh
hdr: zph jql dmg fnm vpp qjl
zhd: qpl xbv
pkj: cql
rqg: srm
mvj: pkj nrr czx
mkq: pbj khz
djf: nfm nsq zmc rgx
nmz: bht qmv
cdd: vxg qdg qms
snr: lmh bzd zbx mmb brh
hnn: htv
tvg: nst
rrt: cll mkj qzp
qdg: fxq
bcf: dll phg prt
bpz: ctn qzn qdl
qpb: lrs vvn jgt hxl
lgm: xrv
cxj: ngb bqc vnn tcn vbq
bbm: xtc qtr
mgm: zfn dfk
cdr: vvr
hzk: htn njh sbg
jfz: mht frp mcb bbk
rpk: rfh pdx
qbt: kvl fnp pxf tzf
zkv: zsk xqd xrv
rgv: znf ftv trr
bhz: pvq mxc tzh
cnz: jrv cnh rzp
pxm: lkv tqh rpg
lvf: gtz xrv stk rhs
krl: zbh
bmt: hdf zxz
tsv: bml lsh bmp jpg
qns: nrv hhr
cnx: zcz tzh fbp gqk
ctc: pnj jnp ctj thc gkg sdh
zds: kvl drx
cmr: kbq nfc kss
hvp: mxc tss fbl
zlh: qzr
sqk: djs nqk qtb
qrt: xpg
ncv: jtk jhj rcs
fvh: ndt lnh vrb prn knm
zvm: fht ccf dcs cmn
dhn: qpn shn
src: drx
qxq: dpn plx hnm
jtk: hxl
pgs: thr hfb
szr: zpz tkq
khj: pqm bsd
cfm: lsz psd
cqx: qqk
pvn: lgm njh csg xbg
vth: crr hrr
tsn: xkf xvv gkr
bss: rzr fhn zgb djf jqr
tgn: fbl pcb zjf
sdq: zdj
crj: grs rtn
phs: kkp csg
tmq: hfx xqp
nzc: krj bhz khj rts
mcl: hhh lrq jbj mcv
xss: sgz
kvp: ldl xxm lff znh cnc
rvp: chn xdb bvv sss hxz
jxr: nzb
nzk: bhh npz kvt kdb
gkr: fth drb vcz pvr mxz hvh
crp: crj mgh
zlt: tnq pzb zqt
pjl: fkb mdx
sdp: lcg djs
shv: xqb
skd: rqg lhg gls
bsn: vms hgp
djv: gbz
klj: qtb szr lcg mkq
mkj: bhh
sbg: dtk
sfx: thc jpt
srs: lgt bhh pkj ctm qqm
gmc: sht sdq kvc frp
pbg: npl pvq
jmr: kjt
gsq: hdm hgr rct
vlk: thr vlq
xnj: lbf mgt csg gdp pnd
mhd: tvb tmc chx
hlv: flj mds
nzf: qqk xdl pnd
lzh: tkv hrb nhg
jbn: xkm
hlx: tnk ggq xxk
hhj: ggz qbn cng hcc
cvj: rbh
dnm: tlm ntf vrv
bbl: tqh cdk xpg sbg xpb
zqv: mhp qdk xsb qqv
jql: rgb pkv bcf lvm
njk: trf tmf
bhh: kkt
lgq: mzl hvb
kpl: htn
nvj: zmf dkl
hfs: znf gfz zbh hjc)"sv;

} // namespace day25
