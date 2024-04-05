import { readFileSync } from 'fs';

function mancala_result(flag, seq, size) {
    const wasmSource = new Uint8Array(readFileSync("./t2-cpp/mancala_result.wasm"));
    const wasmModule = new WebAssembly.Module(wasmSource);

    const wasmInstance = new WebAssembly.Instance(wasmModule, {
        env: {
        }
    });

    const heap = new Uint8Array(wasmInstance.exports.memory.buffer);

    const mancala_result = wasmInstance.exports.mancala_result;
    //处理数组
    const malloc = wasmInstance.exports.self_malloc;
    const free = wasmInstance.exports.self_free;

    const c_array = malloc(size)

    seq.forEach((value, index) => {
        heap[c_array + index * 4] = value;
    });

    // 调用导出的函数
    const ret = mancala_result(flag, c_array, size);
    free(c_array)
    return ret
}

export { mancala_result };