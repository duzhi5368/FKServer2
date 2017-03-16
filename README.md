# FKServer2
A complete game server of 3D MMORPG tlbb.(Without resources)

**Ever tried. Ever failed. No matter. Try Again. Fail again. Fail better.**

## 架构
* 为 BillingSvr 和 LoginSvr 唯一，不依赖 ShareMemory
* WorldSvr 唯一，和 ShareMemory 在同一物理服。
* 其他 Server 和 ShareMemory 一对一的形成一组。
* 一组服务器内应当是 一个 BillingSvr， 一个LoginSvr，一个 （WorldSvr + ShareMemory）组合， N 个 （ Server + ShareMemory ）的组合
