import { readFileSync } from 'fs';

function mancala_operator(flag, status) {
    const wasmSource = new Uint8Array(readFileSync("./mancala_operator.wasm"));
    const wasmModule = new WebAssembly.Module(wasmSource);

    const wasmInstance = new WebAssembly.Instance(wasmModule, {
        env: {
        }
    });

    const heap = new Uint8Array(wasmInstance.exports.memory.buffer);

    const mancala_operator = wasmInstance.exports.mancala_operator;
    //处理数组
    const malloc = wasmInstance.exports.self_malloc;
    const free = wasmInstance.exports.self_free;

    const c_array = malloc(14);

    status.forEach((value, index) => {
        heap[c_array + index * 4] = value;
    });

    // 调用导出的函数
    const ret = mancala_operator(flag, status);
    free(c_array)
    return ret
}

export { mancala_operator };