<h1 style="text-align: center"> Delaunay 三角剖分 </h1>

<h2 style="text-align: center"> Delaunay Triangulation </h2>



## 定义

**三角剖分**：给定一个点集，连线使整个图形被细分为若干三角形。

点集 $P$ 的 $\textbf{Delaunay}$ 三角剖分 $\text{DT}(P)$ 满足条件：

- 空圆性：任意三角形外接圆内没有其他点；若无四点共圆，则 $\text{DT}(P)$ 唯一。
- 最大化最小角：在 $P$ 的所有三角剖分中，$\text{DT}(P)$ 形成的三角形的最小角最大。

<img src="/Users/jason/Desktop/模板/计算几何 Computational Geometry/img/triangulation-1.png" alt="triangulation-1" style="zoom: 50%;" />

## 性质

1. 最接近：以最接近的三点形成三角形，且各线段（三角形的边）皆不相交。
2. 唯一性：不论从区域何处开始构建，最终都将得到一致的结果（点集中任意四点不能共圆）。
3. 最优性：任意两个相邻三角形构成的凸四边形的对角线如果可以互换的话，那么两个三角形六个内角中最小角度不会变化。
4. 最规则：如果将三角剖分中的每个三角形的最小角进行升序排列，则 Delaunay 三角剖分的排列得到的数值最大。
5. 区域性：新增、删除、移动某一个顶点只会影响邻近的三角形。
6. 具有凸边形的外壳：三角剖分最外层的边界形成一个凸多边形的外壳。



## 分治算法构造 $\textbf{Delaunay}$ 三角剖分

1. 将所有点按照横坐标排序；

2. 不断地二分治，直到每一个子点集大小不超过 $3$，此时，每一个子点集自然形成三角形或线段；

   <img src="/Users/jason/Desktop/模板/计算几何 Computational Geometry/img/triangulation-3.svg" style="zoom:33%;" />

3. 回溯时，我们有三种边：$\text{LL-edge},\text{RR-edge},\text{LR-edge}$，分别表示左子点集内部的边，右子点集内部的边，连接左右子集新加的边；为了维持 $\text{DT}$ 的性质，可能需要删除部分 $\text{LL-edge}$ 和 $\text{RR-edge}$，但不会新增 $\text{LL-edge}$ 或 $\text{RR-edge}$。

   <img src="/Users/jason/Desktop/模板/计算几何 Computational Geometry/img/triangulation-4.svg" style="zoom:33%;" />

   合并操作如下：

   1. 插入 $\text{base LR-edge}$，即最底部的不与任何 $\text{LL-edge}$ 和 $\text{RR-edge}$ 相交的边；

      <img src="/Users/jason/Desktop/模板/计算几何 Computational Geometry/img/triangulation-5.svg" style="zoom:33%;" />

   2. 找到与 $\text{base LR-edge}$ 右端点相连的若干 $\text{RR-edge}$，检验它们的端点是否满足条件：

      - $\text{RR-edge}$ 与 $\text{base LR-edge}$ 夹角 $<180^\circ$；
      - $\text{base LR-edge}$ 两端点与该端点确定的圆内无其他点。

      满足上述条件的点作为右侧的可能点。对于左侧，同理可得到左侧的可能点。

      <img src="/Users/jason/Desktop/模板/计算几何 Computational Geometry/img/triangulation-7.svg" style="zoom:33%;" /> <img src="/Users/jason/Desktop/模板/计算几何 Computational Geometry/img/triangulation-8.svg" style="zoom:33%;" />

      若只有一个可能点，则一条 $\text{LR-edge}$ 被添加，删除与之相交的 $\text{LL-edge}$ 和 $\text{RR-edge}$；

      否则，当左右点集均存在可能点时，检查一侧的可能点的圆是否包含另一侧的点，若包含则不符合。

      <img src="/Users/jason/Desktop/模板/计算几何 Computational Geometry/img/triangulation-9.svg" style="zoom:33%;" />

   3. 以添加的 $\text{LR-edge}$ 作为新的 $\text{base LR-edge}$，重复上述过程，直到合并完成。

      <img src="/Users/jason/Desktop/模板/计算几何 Computational Geometry/img/triangulation-10.svg" style="zoom:33%;" />


