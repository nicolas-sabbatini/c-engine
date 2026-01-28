interface Vec2 {
    x: number,
    y: number,
}

function vec2_rotate(v: Vec2, angle: number): Vec2 {
    const cos_a = Math.cos(angle);
    const sin_a = Math.sin(angle);
    return {
        x: v.x * cos_a - v.y * sin_a,
        y: v.x * sin_a + v.y * cos_a,
    };
}

function vec2_rotate_berreta(v: Vec2, angle: number): Vec2 {
    const size = Math.sqrt(v.x * v.x + v.y * v.y)
    const angulo_original = Math.atan2(v.y, v.x)
    const angulo_final = angulo_original + angle

    const x_ratio = Math.cos(angulo_final);
    const y_ratio = Math.sin(angulo_final);

    return {
        x: x_ratio * size,
        y: y_ratio * size,
    }
}

/*
Las 2 funciones son equivalentes y producen el mismo resultado

| Aspecto     | vec2_rotate                 | vec2_rotacion_berreta                        |
|-------------|-----------------------------|----------------------------------------------|
| Operaciones | 4 multiplicaciones, 2 sumas | 2 sqrt, 1 atan2, 2 cos/sin, 2 mult           |
| Rendimiento | ✅ Más rápido               | ❌ Más lento (más funciones trigonométricas) |
| Precisión   | ✅ Ligeramente mejor        | ❌ Acumula más error de punto flotante       |
*/ 