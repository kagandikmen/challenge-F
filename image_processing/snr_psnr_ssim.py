# Python script computing quantitative image regeneration metrics
# Created:      2025-05-16
# Modified:     2025-11-19
# Author:       Kagan Dikmen

import argparse
import numpy as np
from skimage.metrics import structural_similarity

width_orig, height_orig = 256, 256
width_proc, height_proc = 256, 256

def main():

    parser = argparse.ArgumentParser()

    parser.add_argument('-o', '--original',     type=str, required=True)
    parser.add_argument('-p', '--processed',    type=str, required=True)

    args = parser.parse_args()

    # Load images
    with open(args.original, "rb") as f:
        original = np.frombuffer(f.read(), dtype=np.uint8).reshape((height_orig, width_orig))

    with open(args.processed, "rb") as f:
        processed = np.frombuffer(f.read(), dtype=np.uint8).reshape((height_proc, width_proc))

    # Compute SSIM
    score, diff = structural_similarity(original, processed, full=True)
    diff = (diff * 255).astype("uint8")

    # Convert data to float for SNR & PSNR computation
    original = original.astype(np.float32)
    processed = processed.astype(np.float32)

    # Compute SNR and PSNR
    signal_power = np.mean(original ** 2)
    noise_power = np.mean((original - processed) ** 2)
    snr = 10 * np.log10(signal_power / noise_power)
    psnr = 10 * np.log10(255**2 / noise_power)

    # Print to stdout
    print(f"SNR = {snr:.2f} dB")
    print(f"PSNR = {psnr: .2f} dB")
    print(f"SSIM = {score: .3f}")


if __name__ == '__main__':
    main()