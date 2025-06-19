```mermaid
graph TD
    A[F(5)] --> B[F(4)]
    B --> C[F(3)]
    C --> D[F(2)]
    D --> E[F(1)]
    E --> F[基础情况: F(1) = 1]
    F --> G[返回 F(1) = 1]
    G --> H[计算 F(2) = 1+1 = 2]
    H --> I[返回 F(2) = 2]
    I --> J[计算 F(3) = 2+1 = 3]
    J --> K[返回 F(3) = 3]
    K --> L[计算 F(4) = 3+1 = 4]
    L --> M[返回 F(4) = 4]
    M --> N[计算 F(5) = 4+1 = 5]
    N --> O[返回 F(5) = 5]

    style F fill:#f9f,stroke:#333,stroke-width:2px
    style O fill:#bbf,stroke:#333,stroke-width:2px
```
