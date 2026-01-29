interface Vec2 {
    x: number,
    y: number,
}

/*
 * Matriz de rotación 2D - Derivación:
 * 
 * Un punto (x, y) se puede expresar en coordenadas polares como:
 *   x = r * cos(α)
 *   y = r * sin(α)
 * 
 * Donde r es la distancia al origen y α es el ángulo original.
 * 
 * Al rotar por un ángulo θ, el nuevo punto será:
 *   x' = r * cos(α + θ)
 *   y' = r * sin(α + θ)
 * 
 * Usando las identidades de suma de ángulos:
 *   cos(α + θ) = cos(α)cos(θ) - sin(α)sin(θ)
 *   sin(α + θ) = sin(α)cos(θ) + cos(α)sin(θ)
 * 
 * Sustituyendo:
 *   x' = r*cos(α)*cos(θ) - r*sin(α)*sin(θ) = x*cos(θ) - y*sin(θ)
 *   y' = r*sin(α)*cos(θ) + r*cos(α)*sin(θ) = y*cos(θ) + x*sin(θ)
 * 
 * En forma matricial:
 *   | x' |   | cos(θ)  -sin(θ) |   | x |
 *   | y' | = | sin(θ)   cos(θ) | * | y |
 */
function vec2_rotate(v: Vec2, angle: number): Vec2 {
    const cos_a = Math.cos(angle);
    const sin_a = Math.sin(angle);
    return {
        x: v.x * cos_a - v.y * sin_a,
        y: v.x * sin_a + v.y * cos_a,
    };
}

function vec2_rotate_berreta(v: Vec2, angle: number): Vec2 {
    // Calculo el tamaño de mi vector
    const size = Math.sqrt(v.x * v.x + v.y * v.y)
    // Obtengo el angulo de mi vector
    const angulo_original = Math.atan2(v.y, v.x)
    const angulo_final = angulo_original + angle
    // Obtengo el vector unitario del ángulo y lo utilizao como relación
    const x_ratio = Math.cos(angulo_final);
    const y_ratio = Math.sin(angulo_final);
    // Multiplico la relación por el tamaño original para obtener el vector final
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