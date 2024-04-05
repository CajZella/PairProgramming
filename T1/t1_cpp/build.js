import { readFileSync } from 'fs';

function bocchi_shut_up(flag, seq, size) {
    const wasmSource = new Uint8Array(readFileSync("./t1_cpp/t1.wasm"));
    const wasmModule = new WebAssembly.Module(wasmSource);

    const wasmInstance = new WebAssembly.Instance(wasmModule, {
        env: {
        }
    });

    const heap = new Uint8Array(wasmInstance.exports.memory.buffer);

    const bocchi_shut_up = wasmInstance.exports.bocchi_shut_up;
    //处理数组
    const malloc = wasmInstance.exports.self_malloc;
    const free = wasmInstance.exports.self_free;

    const c_array = malloc(size)

    seq.forEach((value, index) => {
        heap[c_array + index * 4] = value;
    });

    // 调用导出的函数
    const ret = bocchi_shut_up(flag, c_array, size);
    free(c_array)
    return ret
}


//const result = await bocchi_shut_up(2, [13, 14, 13, 11, 21, 13, 21, 22], 8);
//console.log(bocchi_shut_up(2, [13, 14, 13, 11, 21, 13, 21, 22], 8))

// 导出包装函数，以便其他 JavaScript 文件可以引入并调用
export { bocchi_shut_up };